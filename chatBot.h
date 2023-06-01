#ifndef PROJECT2_CHATBOT_H
#define PROJECT2_CHATBOT_H

#define WIKI_DEBUG "../wikipedia_100.txt"

#define LEARNED_KB "kbrd"
#define LEARNED_FL "file"

#include <stdio.h>

#define USER_CHATBOT "ChatGTP$ "
#define USER_USER    "me$ "

enum commands {
    CASE_GENERAL = 1,
    CASE_LEARNED_KB,
    CASE_LEARNED_FL,
    CASE_FORGET,
    CASE_ALL_KNOWN,
    CASE_EXIT,
    CASE_FORTY_TWO,
    CASE_PURE_PRINT
};

typedef struct glist {
    char *concept;          // the concept learned
    char *sentence;         // the sentence associated with the concept
    int timesUsed;          //no of times the concept was used to an answer
    char learnedFrom[5];    //learned either from "file" or "kbrd"
    struct glist *next;
    struct glist *prev;
} gtpList;

extern const char *general_responses[];

extern gtpList list_head;

gtpList *genListElement(char *concept,
                        char *sentence,
                        int timesUsed,
                        char *learnedFrom);

char *readLine(FILE *fp);

char *read_string(void);

void readFile(char *filePath, gtpList *head);

int parseStr(const char *str);

void splitStrings(char *source, char *concept, char *sentence, int split);

int parse_command(const char *cp);

int random_custom(int l_bound, h_bound);

#endif // PROJECT2_CHATBOT_H
