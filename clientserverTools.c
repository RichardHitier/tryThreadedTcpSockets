#include "clientserverTools.h"

void error(const char *msg) {
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

void open_and_connect(int *sockfd, char *servername, int portno){
    struct sockaddr_in serv_addr;
    struct hostent *server;

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (*sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(servername);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);

    serv_addr.sin_port = htons(portno);

    if (connect(*sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
}

void write_on_socket(char *buffer, int sockfd){
    int n;
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) error("ERROR writing to socket");
}

void read_from_socket(char *buffer, int sockfd){
    int n;
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) error("ERROR reading from socket");
}

