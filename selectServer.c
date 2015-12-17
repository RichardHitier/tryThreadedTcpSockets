#include "clientserverTools.h"
#include <errno.h>
/* from  http://developerweb.net/viewtopic.php?id=2933 */

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, result;
     fd_set readset;
     char *errStr="";
     char buffer[256];

     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }
    
     portno = atoi(argv[1]);

     open_and_listen(&sockfd, portno);

     get_client_connection(&newsockfd, sockfd);

     do{
         FD_ZERO(&readset);
         FD_SET(newsockfd, &readset);
         result = select( newsockfd + 1, &readset, NULL, NULL, NULL);
     }while(result==-1&&errno==EINTR);

     if ( result > 0){
         if( FD_ISSET( newsockfd, &readset)){
             result=read_from_socket(buffer, newsockfd);
             if (result == 0) {
                 /* This means the other side closed the socket */
                 perror("client closed, we close");
                 close(newsockfd);
             }
             else {
                 /* I leave this part to your own implementation */
                 printf("Here is the message: %s\n",buffer);
             }
         }
     } else if ( result <0){
         sprintf( errStr, "Error on select(): %s", strerror(errno));
         perror(errStr);
     }




//     while( 1 ){
//         read_from_socket(buffer, newsockfd);
//         printf("Here is the message: %s\n",buffer);
//
//         write_on_socket("I got your message", newsockfd);
//     }

     // close everything
     close(newsockfd);
     close(sockfd);
     return 0; 
}
