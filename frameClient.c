#include "clientserverTools.h"


int main(int argc, char *argv[])
{
    int portno;
    int sockfd;
    t_msg_frame ourFrame;


    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);

    open_and_connect(&sockfd, argv[1], portno);

    read_frame_from_socket(&ourFrame,  sockfd);

    print_frame_msg( &ourFrame);

    close(sockfd);
    return 0;
}
