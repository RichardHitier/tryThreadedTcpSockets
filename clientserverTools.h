#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg);
void open_and_listen(int *sockfd, int portno);
void get_client_connection(int *newsockfd, int sockfd);
void open_and_connect(int *sockfd, char *servername, int portno);
void write_on_socket(char *buffer, int sockfd);
void read_from_socket(char *buffer, int sockfd);
