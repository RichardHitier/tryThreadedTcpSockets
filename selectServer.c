/* from  http://developerweb.net/viewtopic.php?id=2933 */
#include "clientserverTools.h"
#include <errno.h>

#define MAXFDS 3

int main(int argc, char *argv[])
{
    int i=0;
    int currfd;
    int mainsockfd, result;
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

    open_and_listen(&mainsockfd, portno);
    FD_SET(mainsockfd, &readset);
    maxfd=mainsockfd;


    // main reading loop
    for(;;){
        printf("in listening loop\n");
        tempset=readset;

        // wait for data
        do{
            result = select( maxfd + 1, &tempset, NULL, NULL, NULL);
        }while(result==-1&&errno==EINTR);

        // got data
        if ( result > 0){
            // is this a new client connexion ?
            if( FD_ISSET( mainsockfd, &tempset) ){
                get_client_connection(&currfd, mainsockfd);
                FD_SET(currfd, &readset);
                maxfd=(maxfd>currfd)?maxfd:currfd;
                printf("%d: Adding  socket num %d; maxfd: %d\n", i++, currfd, maxfd);
                continue;
            } 
            // else scan all openend sockets
            for( currfd=0; currfd<maxfd+1; currfd++){

                if( FD_ISSET( currfd, &tempset)){
                    result=read_from_socket(buffer, currfd);
                    if (result == 0) {
                        // This means the other side closed the socket
                        perror("client closed, we close");
                        FD_CLR(currfd, &readset);
                        close(currfd);
                    }
                    else {
                        printf("Socket %d message: %s\n",currfd, buffer);
                    }
                } 

            }// end for all sockets in list
        } else if ( result <0){
            sprintf( errStr, "Error on select(): %s", strerror(errno));
            perror(errStr);
        }
    }//end main loop


    close(mainsockfd);
    return 0; 
}
