#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Linux multi threads tries.
 *
 * thanks to
 *
 * Pierre Ficheux:
 * http://pficheux.free.fr/articles/lmf/threads/
 *
 * Lucas Pesenti:
 * https://openclassrooms.com/courses/la-programmation-systeme-en-c-sous-unix
 *
 */


typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int var;
} data_t; 
data_t g_data;


void * writing_process(void * arg){
    pthread_mutex_lock(&g_data.mutex);
    g_data.var=5;
    printf("write var before sending signal: %d\n", g_data.var);
    sleep(2);
    pthread_cond_signal(&g_data.cond);
    pthread_mutex_unlock(&g_data.mutex);
    pthread_exit(0);
}

void * reading_process(void * arg){
    pthread_mutex_lock(&g_data.mutex);
    pthread_cond_wait(&g_data.cond, &g_data.mutex);
    printf("reading var after signal received: %d\n", g_data.var);
    pthread_mutex_unlock(&g_data.mutex);
    pthread_exit(0);
}

int main( int argc, char **argv){
    void *ret;
    pthread_t th1, th2;


    if( pthread_mutex_init(&g_data.mutex, NULL))
        perror("MUTEX_INIT FAILED");

    if( pthread_create( &th1, NULL, writing_process, "1")<0){
        perror("THREAD_ERR Couldnt create thread on writing_process");
        return EXIT_FAILURE;
    }

    if( pthread_create( &th2, NULL, reading_process, "2")<0){
        perror("THREAD_ERR Couldnt create thread on reading_process");
        return EXIT_FAILURE;
    }

    if( pthread_join(th1, &ret)){
        perror("pthread_join1");
        return EXIT_FAILURE;
    }

    if( pthread_join(th2, &ret)){
        perror("pthread_join2");
        return EXIT_FAILURE;
    }

    if( pthread_mutex_destroy(&g_data.mutex))
        perror("MUTEX_DESTROY FAILED");;
}
