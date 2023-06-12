#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <stdbool.h>

char *read_line(FILE *fp) {

    char *str = NULL, *cp;
    char ch;
    int len = 0;

    bool whitespace_check = false;

    do {
        ch = fgetc(fp);

        if (ch == '\n' || ch == EOF) {
            ch = '\0';
        }

        if (isspace(ch)) {

            if (whitespace_check)
                continue;

            whitespace_check = true;
            ch = ' ';

        } else {
            whitespace_check = false;
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