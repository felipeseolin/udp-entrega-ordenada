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

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int myStrlen(char str[])
{
    int i = 0;
    int count = 0;
    while (1)
    {
        if (str[i] == '\0' && str[i + 1] == '\0')
        {
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

void myStrcpy(char newString[][MAXLINE], char oldString[][MAXLINE], int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        strcpy(newString[j], oldString[j]);
    }
}

int myStrcmp(char string1[][MAXLINE], char string2[][MAXLINE], int i)
{
    int j;
    for (j = 0; j < i; j++)
    {
        if (strcmp(string1[j], string2[j]) != 0)
        {
            return FALSE;
        }
    }
}

void takeofFirstChar(char string[][MAXLINE], int i)
{
    int j;
    int k;
    for (j = 0; j <= i; j++)
    {
        for (k = 0; k < strlen(string[j]); k++)
        {
            string[j][k] = string[j][k + 1];
        }
        string[j][k] = '\0';
    }
}

int trimString(char buffer[], char output[][MAXLINE])
{
    char *p;
    int i = 0;
    p = buffer;
    while (*p != '\0')
    {
        strcpy(output[i++], p);
        p += strlen(p) + 1;
    }
    return i;
}

// Driver code
int main()
{
    int sockfd;
    char buffer[MAXLINE];
    char *hello = "Mensagem recebida, iremos ordená-la se preciso";
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
    
    // Information
    int len, n;
    n = recvfrom(sockfd, (char *)buffer, MAXLINE,
                 MSG_WAITALL, (struct sockaddr *)&cliaddr,
                 &len);
    buffer[n] = '\0';
    printf("Client : %s\n", buffer);

    sendto(sockfd, (const char *)hello, strlen(hello),
           MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
           len);
    printf("Hello message sent.\n");

    char output[MAXLINE][MAXLINE];
    // char compare[MAXLINE][MAXLINE];

    int i = trimString(buffer, output);
    // myStrcpy(compare, output, i);

    // qsort(output, i, MAXLINE, cmpfunc);
    // takeofFirstChar(output, i);
    printf("\n----Mensagem recebida ordenada: ----\n");
    // print(output, i);

    return 0;
}