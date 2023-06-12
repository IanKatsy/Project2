#include "chatBot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include <ctype.h>

int parse_str(const char *str) {

    int i = 0;

    while (1) {
        if (*(str + i) == 0)
            return -1;

        if (*(str + i) == ':')
            return i;

        i++;
    }

}

void split_strings(char *source, char **concept, char **sentence, int split) {

    if (*concept != NULL || *sentence != NULL) {
        printf("concept or sentences aren't NULL");
    }

    size_t len = strlen(source);

    int i;

    char *get_concept = malloc(split + 1);

    if (get_concept == NULL) {
        perror("malloc() returned a NULL pointer!\n");
        exit(0);
    }

    *concept = get_concept;

    for (i = 0; i < split; i++) {
        get_concept[i] = source[i];
    }

    size_t length = len - split;
    char *get_sentence = malloc(length);

    if (get_sentence == NULL) {
        perror("malloc() returned a NULL pointer!\n");
        exit(0);
    }

    *sentence = get_sentence;

    for (i = 0; i < length; i++) {
        get_sentence[i] = source[i + split + 1];
    }

    free(source);

}

int parse_command(const char *cp) {

    if (!strncmp(cp, COMMAND_LEARN_KB, strlen(COMMAND_LEARN_KB)))
        return CASE_LEARNED_KB;

    if (!strncmp(cp, COMMAND_LEARN_FL, strlen(COMMAND_LEARN_FL)))
        return CASE_LEARNED_FL;

    if (!strncmp(cp, COMMAND_FORGET, strlen(COMMAND_FORGET)))
        return CASE_FORGET;

    if (!strcasecmp(cp, COMMAND_LEAVE))
        return CASE_EXIT;

    if (!strcasecmp(cp, COMMAND_FORTY_TWO))
        return CASE_FORTY_TWO;

    if (!strcasecmp(cp, COMMAND_ALL_KNOWLEDGE))
        return CASE_ALL_KNOWN;

    if (!strcasecmp(cp, COMMAND_PURE_PRINT))
        return CASE_PURE_PRINT;


    return CASE_GENERAL;
}

void str_to_upper(char *string) {

    size_t len = strlen(string);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(*(string + i))) {
            *(string + i) = (char) toupper(*(string + i));
        }
    }

}

int compare_strings(char *string1, char *string2) { // strcmp was acting up

    int i;

    for (i = 0; i < strlen(string1); i++) {
        if (string1[i] != string2[i]) {
            break;
        }
    }

    return string1[i] - string2[i];

}