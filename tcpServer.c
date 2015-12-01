#include "clientserverTools.h"

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     char buffer[256];
     int n;

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
    
     portno = atoi(argv[1]);

     open_and_listen(&sockfd, portno);

     get_client_connection(&newsockfd, sockfd);

     while( 1 ){
         read_from_socket(buffer, newsockfd);
         printf("Here is the message: %s\n",buffer);

         write_on_socket("I got your message", newsockfd);
     }

     // close everything
     close(newsockfd);
     close(sockfd);
     return 0; 
}
