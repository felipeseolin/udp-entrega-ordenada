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

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

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
    char output[150][150];

    char *p;
    int i = 0;
    p = buffer;
    while (*p != '\0')
    {
        strcpy(output[i++], p);
        p += strlen(p) + 1;
    }

    qsort(output, i, 150, cmpfunc);

    int j;
    int k;
    for (j = 0; j <= i; j++) {
        for(k = 0; k < strlen(output[j]); k++) {
            output[j][k] = output[j][k + 1];
        }
        output[j][k] = '\0';
    }

    for (j = 0; j < i; j++) {
        printf("%s\n", output[j]);
    }

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("\n\nHello message sent.\n\n");

    return 0;
}
