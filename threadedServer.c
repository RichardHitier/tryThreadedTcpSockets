#include <pthread.h>
#include "clientserverTools.h"

int newsockfd;

void *reading_process(void *arg){
     char buffer[256];
     while( 1 ){
         read_from_socket(buffer, newsockfd);
         printf("Here is the message: %s\n",buffer);
     }
}

void *writing_process(void *arg){
    while(1){
         write_on_socket("I got your message", newsockfd);
     }
}


int main(int argc, char *argv[])
{
    void* ret;
     int sockfd, portno;
     int n;
     pthread_t th1, th2;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
    
     portno = atoi(argv[1]);

     open_and_listen(&sockfd, portno);

     get_client_connection(&newsockfd, sockfd);

     pthread_create( &th1, NULL, reading_process, NULL);
     pthread_create( &th2, NULL, writing_process, NULL);

     pthread_join(th1, &ret);
     pthread_join(th2, &ret);

     // close everything
     close(newsockfd);
     close(sockfd);
     return 0; 
}
