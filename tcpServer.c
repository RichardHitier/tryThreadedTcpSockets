/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

void open_and_listen(int *sockfd, int portno){
     struct sockaddr_in serv_addr;
     // open socket to listen to
     *sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (*sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(*sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(*sockfd,5);
}

void get_client_connection(int *newsockfd, int sockfd){
    struct sockaddr_in cli_addr;
    
     // get client connection
     socklen_t clilen = sizeof(cli_addr);
     *newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (*newsockfd < 0) 
          error("ERROR on accept");
}

void read_from_socket(char *buffer, int newsockfd){
    int n;
    // read from socket
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
}

void write_on_socket(char *message, int newsockfd){
    int n;
    // write to socket
    n = write(newsockfd,message,sizeof(message));
    if (n < 0) error("ERROR writing to socket");
}

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
