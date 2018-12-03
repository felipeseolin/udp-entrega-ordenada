#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 150
#define TRUE 1
#define FALSE 0

int cmpfunc(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    char str[LEN] = "cTeste\0bTeste\0aTeste\0\0";
    char output[LEN][LEN];

    char *p;
    int i = 0;
    p = str;
    while(*p != '\0') {
        // printf("\n%s\n\n", p);
        // output[i++] = p;
        strcpy(output[i++], p);
        p += strlen(p) + 1;
    }

    qsort(output, i, LEN, cmpfunc);

    int j;
    for(j = 0; j < i; j++) {
        printf("%s\n", output[j]);
    }

    return 0;
}