#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h>     /* for close() */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32   /* Size of receive buffer */

void DieWithError(char *errorMessage);  /* Error handling function */

void HandleTCPClient(int clntSocket)
{
    printf("Hello world, i am HandleTCPClient\n");
    char echoBuffer[RCVBUFSIZE];        /* Buffer for echo string */
    int recvMsgSize;                    /* Size of received message */
    char target_addr[20];
    int target_addr_len = 0;
    char portString[10];
    int portLen = 0;
    int port = -1;

    char echoString[RCVBUFSIZE + 1];
    int echoStringLen = -1;




    /* Receive message from client */
    if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
        DieWithError("recv() failed");

    printf("log: recv() worked fine\n");
    if (recvMsgSize == 0) {
        printf("zero length message, skipping\n");
        close(clntSocket);
        return;
    }

    char* t = echoBuffer;

    while (*t++ != ':');
    target_addr_len = (t - echoBuffer) - 1;
    strncpy(target_addr, echoBuffer, target_addr_len);
    target_addr[target_addr_len] = '\0';

    char* tt = t;

    while (*t++ != '|');
    portLen = (t - tt);
    strncpy(portString, tt, portLen);
    portString[portLen] = '\0';
    port = atoi(portString);
    printf("now printing info about input signal\n");

    printf("log: addr is %s, port is %d, message is %s\n", target_addr, port, t);


    // copied from client

    int sock;
    struct sockaddr_in echoServAddr; /* Echo server address */


    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct ANOTHER CLIENT address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(target_addr);   /* Server IP address */
    echoServAddr.sin_port        = htons(port); /* Server port */


    printf("Sending message to  IP address = %s. and port %d Wait...\n", inet_ntoa(echoServAddr.sin_addr), port);
    /* Establish the connection to ANOTHER CLIENT */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

    printf("log: connect() worked fine - connected to second client\n");

    //echoStringLen = strlen(echoString);          /* Determine input length */

    /* Send the string to ANOTHER CLIENT */
    if (send(sock, "regular_message_to_send\0", strlen("regular_message_to_send\0") + 1, 0) != strlen("regular_message_to_send\0") + 1)
        DieWithError("send() sent a different number of bytes than expected");

    printf("log: send() worked fine - sent data to second client\n");


    close(sock);





    //////////////////////////////////////
    close(clntSocket);
}
