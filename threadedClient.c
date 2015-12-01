#include <pthread.h>
#include "clientserverTools.h"

int sockfd;

void *writing_process(void *arg){
	int i=0;
    char buffer[256];
    while(1){
        printf("%d Please enter the message: ", i++);

        bzero(buffer,256);
        fgets(buffer,255,stdin);

        write_on_socket(buffer, sockfd);
    }
}

void *reading_process(void *arg){
    char buffer[256];
    while(1){
        read_from_socket(buffer, sockfd);
        printf("I have read: %s\n",buffer);
    }
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

    open_and_connect(&sockfd, argv[1], portno);
    pthread_create( &th1, NULL, reading_process, NULL);
    pthread_create( &th2, NULL, writing_process, NULL);

    pthread_join(th1, &ret);
    pthread_join(th2, &ret);



    close(sockfd);
    return 0;
}
