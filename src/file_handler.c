#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>

char *readLine(FILE *fp) {

    char *str = NULL, *cp;
    char ch;
    int len = 0;

    do {
        ch = fgetc(fp);

        if (ch == '\n' || ch == EOF) {
            ch = '\0';
        }

        len++;

        cp = realloc(str, len);

        if (cp == NULL) {
            perror("realloc() returned a NULL pointer");
            exit(EXIT_FAILURE);
        }

        str = cp;

        str[len - 1] = ch;

    } while (ch != '\0');

    return str;
}