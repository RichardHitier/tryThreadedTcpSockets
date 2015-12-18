/* from  http://developerweb.net/viewtopic.php?id=2933 */
#include "clientserverTools.h"
#include <errno.h>

#define MAXFDS 3

int main(int argc, char *argv[])
{
    int i;
    int currfd;
    int sockfd, result;
    int maxfd;
    int portno=DEFPORT;

    fd_set readset, tempset;

    char *errStr="";
    char buffer[256];

    // allow to get port on CLI
    if (argc > 2) {
        portno = atoi(argv[1]);
    }


    FD_ZERO(&readset);
    FD_ZERO(&tempset);

    open_and_listen(&sockfd, portno);


    // wait for all MAXFDS connections
    for( i=0; i<MAXFDS; i++){
        get_client_connection(&currfd, sockfd);
        FD_SET(currfd, &readset);
        maxfd=(maxfd>currfd)?maxfd:currfd;
        printf("%d: Adding  socket num %d; maxfd: %d\n", i, currfd, maxfd);
    }
    printf("ok, done with connecting socket to list\n");

    // main reading loop
    for(;;){
        printf("in listening loop\n");
        tempset=readset;

        // wait for data
        do{
            result = select( maxfd + 1, &tempset, NULL, NULL, NULL);
            printf("\rgot result: %d", result);
        }while(result==-1&&errno==EINTR);
        printf("Hey ! result: %d\n", result);

        // got data
        if ( result > 0){
            // scan all openend sockets
            for( currfd=0; currfd<maxfd+1; currfd++){
                //printf("Does %d has ?\n", currfd);
                if( FD_ISSET( currfd, &tempset)){
                    printf("yes %d has\n", currfd);
                    result=read_from_socket(buffer, currfd);
                    if (result == 0) {
                        /* This means the other side closed the socket */
                        perror("client closed, we close");
                        FD_CLR(currfd, &readset);
                        //close(currfd);
                        // TODO: we should release the
                        // socket in the list ! and be able
                        // to accept new connection
                    }
                    else {
                        printf("Here is the message: %s\n",buffer);
                    }
                } 

            }// end for all sockets in list
        } else if ( result <0){
            sprintf( errStr, "Error on select(): %s", strerror(errno));
            perror(errStr);
        }
    }//end main loop


    close(sockfd);
    return 0; 
}
