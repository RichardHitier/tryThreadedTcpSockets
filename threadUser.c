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
    pthread_mutex_t g_mutex;
    int g_var;
} data_t; 
data_t new_data;

// g_condition


void * writing_process(void * arg){
    pthread_mutex_lock(&new_data.g_mutex);
    new_data.g_var=5;
    printf("writen g_var: %d\n", new_data.g_var);
    sleep(1);
    pthread_mutex_unlock(&new_data.g_mutex);
    pthread_exit(0);
}

void * reading_process(void * arg){
    pthread_mutex_lock(&new_data.g_mutex);
    printf("reading g_var: %d\n", new_data.g_var);
    sleep(1);
    pthread_mutex_unlock(&new_data.g_mutex);
    pthread_exit(0);
}

int main( int argc, char **argv){
    void *ret;
    pthread_t th1, th2;


    if( pthread_mutex_init(&new_data.g_mutex, NULL))
        perror("MUTEX_INIT FAILED");

    if( pthread_create( &th1, NULL, writing_process, "1")<0){
        perror("THREAD_ERR Couldnt create thread on writing_process");
        return EXIT_FAILURE;
    }
    if( pthread_join(th1, &ret)){
        perror("pthread_join1");
        return EXIT_FAILURE;
    }

    printf("Didnt event created the 2nd thread\n");

    if( pthread_create( &th2, NULL, reading_process, "2")<0){
        perror("THREAD_ERR Couldnt create thread on reading_process");
        return EXIT_FAILURE;
    }
    if( pthread_join(th2, &ret)){
        perror("pthread_join2");
        return EXIT_FAILURE;
    }

    if( pthread_mutex_destroy(&new_data.g_mutex))
        perror("MUTEX_DESTROY FAILED");;
}
