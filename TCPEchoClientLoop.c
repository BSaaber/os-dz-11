#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */

#define RCVBUFSIZE 32   /* Size of receive buffer */
#define MAXPENDING 5    /* Maximum outstanding connection requests */

void DieWithError(char *errorMessage);  /* Error handling function */
void ClientReciever(int clntSocket);

int main(int argc, char *argv[])
{
    int sock;                        /* Socket descriptor */
    struct sockaddr_in echoServAddr; /* Echo server address */
    unsigned short echoServPort, listenerPort;     /* Echo server port */
    char *servIP;                    /* Server IP address (dotted quad) */
    char *echoString;                /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE];     /* Buffer for echo string */
    unsigned int echoStringLen;      /* Length of string to echo */
    int bytesRcvd, totalBytesRcvd;   /* Bytes read in single recv()
                                        and total bytes read */

    if (0)    /* Test for correct number of arguments */
    {
       fprintf(stderr, "Usage: %s <Server IP> <Server Port> <Listener Port>\n",
               argv[0]);
       exit(1);
    }

    servIP = argv[1];             /* First arg: server IP address (dotted quad) */

    echoServPort = atoi(argv[2]); /* Use given port, if any */
    listenerPort = atoi(argv[3]);





    int processID;
    if ((processID = fork()) < 0)
        DieWithError("fork() failed\n");


    if (processID != 0) {


        printf("log: i am father client process, my pid is %d\n", getpid());




    /* Create a reliable, stream socket using TCP */
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    printf("log: socket() worked fine\n");

    /* Construct the server address structure */
    memset(&echoServAddr, 0, sizeof(echoServAddr));     /* Zero out structure */
    echoServAddr.sin_family      = AF_INET;             /* Internet address family */
    echoServAddr.sin_addr.s_addr = inet_addr(servIP);   /* Server IP address */
    echoServAddr.sin_port        = htons(echoServPort); /* Server port */

    /* Establish the connection to the echo server */
    if (connect(sock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr)) < 0)
        DieWithError("connect() failed");

        printf("log: connect() worked fine\n");


    for(; ;) {
        sleep(2);
        //scanf("%s", echoString);
        echoString = "127.0.0.1:13|maxem\0";
        echoStringLen = strlen(echoString) + 1;
        printf("log: input string is %s\n", echoString);

        /* Send the string to the server */
        if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
            DieWithError("send() sent a different number of bytes than expected");

        printf("log: send() worked fine\n");

//        /* Receive the same string back from the server */
//        totalBytesRcvd = 0;
//        printf("Received: ");            // Setup to print the echoed string
//        while (totalBytesRcvd < echoStringLen) {
//            /* Receive up to the buffer size (minus 1 to leave space for
//            a null terminator) bytes from the sender */
//            if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
//                DieWithError("recv() failed or connection closed prematurely");
//            totalBytesRcvd += bytesRcvd;   /* Keep tally of total bytes */
//            echoBuffer[bytesRcvd] = '\0';  /* Terminate the string! */
//            printf("%s", echoBuffer);      /* Print the echo buffer */
//        }

        printf("\n");    /* Print a final linefeed */
        sleep(2);
    }

    close(sock);

    }



    else


    {
        //sleep(5);
        printf("log: i am child client process, my pid is %d\n", getpid());

    // Listening logic, will be forked



    int servSock;                    /* Socket descriptor for server */
    int clntSock;                    /* Socket descriptor for client */
    struct sockaddr_in localAddr; /* Local address */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int clntLen;            /* Length of client address data structure */




    /* Create socket for incoming connections */
    if ((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");

    /* Construct local address structure */
    memset(&localAddr, 0, sizeof(localAddr));   /* Zero out structure */
    localAddr.sin_family = AF_INET;                /* Internet address family */
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    localAddr.sin_port = htons(listenerPort);      /* Local port */

    /* Bind to the local address */
    if (bind(servSock, (struct sockaddr *) &localAddr, sizeof(localAddr)) < 0)
        DieWithError("bind() failed");

    printf("Server IP address = %s. port is %d Wait...\n", inet_ntoa(localAddr.sin_addr), listenerPort);

    /* Mark the socket so it will listen for incoming connections */
    if (listen(servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");


    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);

        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr,
                               &clntLen)) < 0)
            DieWithError("accept() failed");

        /* clntSock is connected to a client! */
        printf("ensuring this is connection with 7th port. port of sender is: %d\n", echoClntAddr.sin_port);

        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));

        ClientReciever(clntSock);
    }


    } // end of child

    //////////////////////


    exit(0);
}
