// Client side implementation of UDP client-server model
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

// Driver code
int myStrlen(char str[]){
    int i = 0;
    int count  = 0;
    while(1) {
        if(str[i] == '\0' && str[i+1]== '\0'){
            return count + 2;
        }
        count++;
        i++;
    }
    return count;
}

void print(char string[][MAXLINE], int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        printf("%s\n", string[j]);
    }
}

int main()
{
    int sockfd;
    // char buffer[MAXLINE];
    char *hello = "bTesteB\0cTesteC\0aTesteA\0\0";
    struct sockaddr_in servaddr;

    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int n, len;

    int v = sendto(sockfd, (const char *)hello, myStrlen(hello),
                   MSG_CONFIRM, (const struct sockaddr *)&servaddr,
                   sizeof(servaddr));
    if(v < 0) {
        printf("\n Ocorreu um erro e sua mensagem não foi enviada\n\n");
    }
    printf("\n\nSua mensagem foi enviada\n\n");

    close(sockfd);
    return 0;
}
