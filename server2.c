// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024
#define TRUE 1
#define FALSE 0

// Driver code

int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char buffer2[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Olá, eu sou o servidor\nEsperando respostas...\n\n\n");
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    printf("\nErro");
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);
    buffer[n] = '\0';
    char arr[sizeof(buffer)];
    strcpy(arr, buffer);
    int le = sizeof(arr) / sizeof(arr[0]);

    int i = 0;
    int j = 0;
    char palavra[] = "/0";

    for (j = 0; j < strlen(arr); j++) {
        if(arr[j + 1] == '\0') {
            break;
        }
        int barraZero = FALSE;
        int i = 0;
        while(barraZero == FALSE) {
            palavra[i] = arr[i];
            if (arr[i] == '\0') {
                barraZero = TRUE;
            }
        }
        for (i = 0; i < strlen(palavra); i++) {
            if (palavra[i] == '\0') {
                buffer2[i - 1] = '\0';
                break;
            }
            buffer2[i - 1] = palavra[i];
        }
        printf("Client : %s\n", buffer2);
    }

    // printf("Client : %s\n", buffer2);

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("Hello message sent.\n");

    return 0;
}
