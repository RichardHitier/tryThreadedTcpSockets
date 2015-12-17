/* from  http://developerweb.net/viewtopic.php?id=2933 */
#include "clientserverTools.h"
#include <errno.h>
#include <sys/time.h>

#define MAXFDS 3
#define MAX_BUFFER_SIZE 256


int main(int argc, char **argv){

    fd_set readset, tempset;
    int maxfd; 
    int srvsock, peersock, j, result, result1, sent, len;
    struct timeval tv;
    char buffer[MAX_BUFFER_SIZE+1];
    struct sockaddr_in addr;

    int portno = DEFPORT;

    /* Here should go the code to create the server socket bind it to a port and call listen
       srvsock = socket(...);
       bind(srvsock ...);
       listen(srvsock ...);
       */
    open_and_listen(&srvsock, portno);

    FD_ZERO(&readset);
    FD_SET(srvsock, &readset);
    maxfd = srvsock;

    do {
        memcpy(&tempset, &readset, sizeof(tempset));
        tv.tv_sec = 30;
        tv.tv_usec = 0;
        result = select(maxfd + 1, &tempset, NULL, NULL, &tv);

        if (result == 0) {
            printf("select() timed out!\n");
        }
        else if (result < 0 && errno != EINTR) {
            printf("Error in select(): %s\n", strerror(errno));
        }
        else if (result > 0) {

            if (FD_ISSET(srvsock, &tempset)) {
                len = sizeof(addr);
                peersock = accept(srvsock, &addr, &len);
                if (peersock < 0) {
                    printf("Error in accept(): %s\n", strerror(errno));
                }
                else {
                    FD_SET(peersock, &readset);
                    maxfd = (maxfd < peersock)?peersock:maxfd;
                }
                FD_CLR(srvsock, &tempset);
            }

            for (j=0; j<maxfd+1; j++) {
                if (FD_ISSET(j, &tempset)) {

                    do {
                        result = recv(j, buffer, MAX_BUFFER_SIZE, 0);
                    } while (result == -1 && errno == EINTR);

                    if (result > 0) {
                        buffer[result] = 0;
                        printf("Echoing: %s\n", buffer);
                        sent = 0;

                        do {
                            result1 = send(j, buffer+sent, result-sent, MSG_NOSIGNAL);
                            if (result1 > 0)
                                sent += result1;
                            else if (result1 < 0 && errno != EINTR);
                            break;
                        } while (result > sent);

                    }
                    else if (result == 0) {
                        close(j);
                        FD_CLR(j, &readset);
                    }
                    else {
                        printf("Error in recv(): %s\n", strerror(errno));
                    }
                }      // end if (FD_ISSET(j, &tempset))
            }      // end for (j=0;...)
        }      // end else if (result > 0)
    } while (1);
}
