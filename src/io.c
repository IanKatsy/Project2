#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <stdbool.h>

char *read_string(void) {

    char *str = NULL, *cp;
    char ch;
    int len = 0;

    bool whitespace_check = false;

    do {
        ch = getchar();

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

        cp = realloc(str, len * sizeof(char));

        if (cp == NULL) {
            perror("realloc() returned a NULL pointer");
            exit(EXIT_FAILURE);
        }

        str = cp;

        str[len - 1] = ch;

    } while (ch != '\0');

    return str;
}


int read_file(const char *filePath) {

    printf("FILEPATH '%s'\n",
           filePath);

    FILE *fp = fopen(filePath,
                     "r");

    if (fp == NULL) {
        fprintf(stdout,
                "fopen() returned a NULL pointer, possibly file doesn't exist or user doesn't have correct permissions!\n");
        fprintf(dialog,
                "fopen() returned a NULL pointer, possibly file doesn't exist or user doesn't have correct permissions!\n");
        return 1;
    }

    char *str;
    int line_count = 0;

    while (!feof(fp)) {

        line_count++;

        str = read_line(fp);
        int split = parse_str(str);

        if (split == PARSE_ERROR) {
            fprintf(stdout, "Format error in line %d!\n", line_count);
            fprintf(dialog, "Format error in line %d!\n", line_count);
            free(str);
            continue;
        }

        char *concept = NULL, *sentence = NULL;

        split_strings(str, &concept, &sentence, split);

        gen_node(concept, sentence, 0, LEARNED_FL);
    }

    fclose(fp);

    return 0;
}
