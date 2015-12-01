#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// g_mutex
// g_condition

void * cb1(void * arg){
    printf("in callback cb1 %s\n", (char*)arg);
    pthread_exit(0);
}

void * cb2( void *arg){
    pthread_exit(0);
}

int main( int argc, char **argv){
    pthread_t th1;
    void *ret;

    if( pthread_create( &th1, NULL, cb1, "hello world")<0){
        perror("THREAD_ERR Couldnt create thread");
        exit(1);
    }
    (void)pthread_join(th1, &ret);
}
