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

#ifndef COMMANDS_PARSE
#define COMMANDS_PARSE

#define COMMAND_LEARN_KB      "learn this > "
#define COMMAND_LEARN_FL      "read this > "
#define COMMAND_FORGET        "forget this > "
#define COMMAND_LEAVE         "So Long, and Thanks for All the Fish"
#define COMMAND_FORTY_TWO     "What is the meaning of Life, The Universe, and Everything?"
#define COMMAND_ALL_KNOWLEDGE "What do you know about?"
#define COMMAND_PURE_PRINT    "What do you talk about?"

#endif

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