#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * Linux multi threads tries.
 *
 * thank you to Pierre Ficheux:
 * http://pficheux.free.fr/articles/lmf/threads/
 */

// g_mutex
// g_condition

void * cb1(void * arg){
    int i;
    for(i=0; i<5; i++){
        printf("Thread %s: %d\n", (char*)arg, i);
        sleep(1);
    }
    pthread_exit(0);
}

int main( int argc, char **argv){
    pthread_t th1, th2;
    void *ret;

    if( pthread_create( &th1, NULL, cb1, "1")<0){
        perror("THREAD_ERR Couldnt create thread");
        exit(1);
    }
    if( pthread_create( &th2, NULL, cb1, "2")<0){
        perror("THREAD_ERR Couldnt create thread");
        exit(1);
    }
    (void)pthread_join(th1, &ret);
    (void)pthread_join(th2, &ret);
}
