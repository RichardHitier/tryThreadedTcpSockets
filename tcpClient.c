#include "clientserverTools.h"

int main(int argc, char *argv[])
{
    int sockfd, portno, n, i=0;

    char buffer[256];

    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);

    open_and_connect(&sockfd, argv[1], portno);

    while(1){
        printf("%d Please enter the message: ", i++);

        bzero(buffer,256);
        fgets(buffer,255,stdin);

        write_on_socket(buffer, sockfd);
        read_from_socket(buffer, sockfd);


        printf("I have read: %s\n",buffer);
    }
    close(sockfd);
    return 0;
}
