#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *reading_process(void *arg){
    printf("reading_process\n");
}
void *writing_process(void *arg){
    printf("writing_process\n");
}

int main(int argc, char **argv){
    pthread_t th_tab[2];
    void * ret;

    pthread_create(&(th_tab[1]),NULL, writing_process, NULL);
    pthread_create(&(th_tab[2]),NULL, reading_process, NULL);

    pthread_join(th_tab[1], &ret);
    pthread_join(th_tab[2], &ret);
}
