#include "chatBot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int parseStr(const char *str) {

    int i = 0;

    while (1) {
        if (*(str + i) == 0)
            return -1;

        if (*(str + i) == ':')
            return i;

        i++;
    }

}

void splitStrings(char *source, char *concept, char *sentence, int split) {

    size_t len = strlen(source);

    int i;

    concept = malloc(split + 1);

    for (i = 0; i < split; i++) {
        concept[i] = source[i];
    }

    size_t length = len - split;
    sentence = malloc(length);

    for (i = 0; i < length; i++) {
        sentence[i] = source[i + split + 1];
    }

    free(source);

}