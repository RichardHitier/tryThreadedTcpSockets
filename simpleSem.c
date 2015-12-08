#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t g_sem;
int the_end;

void *reading_process(void *arg){
    while(!the_end){
        printf("READING: waiting\n");
        sem_wait(&g_sem);
        printf("READING: got sem\n");
    }
    printf("READING: reading exit");
    pthread_exit(0);
}
void *writing_process(void *arg){
    int i;
    for(i=0; i<5;i++){
        printf("WRITING in 2 sec:\n\n");
        sleep(2);
        sem_post(&g_sem);
    }
    the_end=1;
    sem_post(&g_sem);
    pthread_exit(0);
}

int main(int argc, char **argv){
    pthread_t th_tab[2];
    void * ret;

    the_end=0;

    pthread_create(&(th_tab[1]),NULL, writing_process, NULL);
    pthread_create(&(th_tab[2]),NULL, reading_process, NULL);

    pthread_join(th_tab[1], &ret);
    pthread_join(th_tab[2], &ret);

    return EXIT_SUCCESS;
}
