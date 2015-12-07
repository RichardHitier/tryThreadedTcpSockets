#include "clientserverTools.h"



int main(int argc, char *argv[])
{
    int newsockfd;
    void* ret;
    int sockfd, portno;
    int n;
    t_msg_frame ourFrame={1,2,3,"hello world",5};

    if (argc < 2) {
     fprintf(stderr,"ERROR, no port provided\n");
     exit(1);
    }

    portno = atoi(argv[1]);

    open_and_listen(&sockfd, portno);

    get_client_connection(&newsockfd, sockfd);

    write_frame_on_socket(&ourFrame, newsockfd);

    // close everything
    close(newsockfd);
    close(sockfd);
    return 0; 
}
