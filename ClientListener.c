#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <string.h>
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

int ClientReciever(int clntSocket)
{
   // printf("log: HELLO WORLD, I AM CLIENT LISTENER\n");
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */

    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");
   // printf("log: client listener recieved data\n");
   // printf("log: first three letters are %c %c %c\n", echoBuffer[0], echoBuffer[1], echoBuffer[2]);
   // printf("log: recv message size: %d\n", recvMsgSize);
    for (int i = 0; i < recvMsgSize - 1; ++i) {
	    printf("%c", echoBuffer[i]);
    }
   
    printf("\n");
    if (recvMsgSize == 8 && echoBuffer[0] == 'T' &&
		    echoBuffer[1] == 'h' &&
		    echoBuffer[2] == 'e' &&
		    echoBuffer[3] == ' ' &&
		    echoBuffer[4] == 'E' &&
		    echoBuffer[5] == 'n' &&
		    echoBuffer[6] == 'd') {
	    return -1;
    }
   // printf("log: closing reading\n");
    close(clntSocket);    /* Close client socket */
   // printf("log: closed reading \n");
   return 0;
}

