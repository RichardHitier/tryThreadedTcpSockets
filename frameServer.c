#include "clientserverTools.h"



int main(int argc, char *argv[])
{
    int newsockfd;
    int sockfd, portno;
    t_msg_frame ourFrame={1,2,3,"goodbye cruel world",5};
    ourFrame.bdyLgth=strlen(ourFrame.msgBody);

    if (argc < 2) {
     fprintf(stderr,"ERROR, no port provided\n");
     exit(1);
    }

    if ( argc > 2){
        // todo: kindof msgBodyCpy()
        ourFrame.msgBody=malloc(strlen(argv[2]));
        strcpy(ourFrame.msgBody, argv[2]);
        ourFrame.bdyLgth=strlen(ourFrame.msgBody);
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
