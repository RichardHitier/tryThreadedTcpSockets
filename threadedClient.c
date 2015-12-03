#include <pthread.h>
#include "clientserverTools.h"

static pthread_mutex_t my_mutex;
int sockfd;
int gcondition=1;

void *writing_process(void *arg){
	int i=0;
    char buffer[256];
    while(1){
        bzero(buffer,256);

        fprintf(stderr,"%d Please enter the message: ", i++);

        fgets(buffer,255,stdin);

        // set gcondition to false
        pthread_mutex_lock (&my_mutex);
        gcondition=0;
        pthread_mutex_unlock (&my_mutex);

        write_on_socket(buffer, sockfd);
    }
    pthread_exit (0);
}

void *reading_process(void *arg){
    char buffer[256];
    int count=0;
    int lcondition;
    while(1){
        lcondition=gcondition;
        while(lcondition){
            read_from_socket(buffer, sockfd);
            count++;
            // lock doesnt wait
            pthread_mutex_trylock (&my_mutex);
            lcondition=gcondition;
            pthread_mutex_unlock (&my_mutex);
        }
        fprintf(stderr,"%d Read\n",count);
        count=0;
        pthread_mutex_trylock (&my_mutex);
        gcondition=1;
        pthread_mutex_unlock (&my_mutex);
    }
    pthread_exit (0);
}

int main(int argc, char *argv[])
{
    int portno;

    pthread_t th1, th2;
    void* ret;


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);

    pthread_mutex_init (&my_mutex, NULL);

    open_and_connect(&sockfd, argv[1], portno);
    pthread_create( &th1, NULL, reading_process, NULL);
    pthread_create( &th2, NULL, writing_process, NULL);

    pthread_join(th1, &ret);
    pthread_join(th2, &ret);



    close(sockfd);
    return 0;
}
