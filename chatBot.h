#ifndef PROJECT2_CHATBOT_H
#define PROJECT2_CHATBOT_H

#define WIKI_DEBUG "../wikipedia_100.txt"

#define LEARNED_KB "kbrd"
#define LEARNED_FL "file"

#include <stdio.h>

typedef struct glist {
    char *concept;          // the concept learned
    char *sentence;         // the sentence associated with the concept
    int timesUsed;          //no of times the concept was used to an answer
    char learnedFrom[5];    //learned either from "file" or "kbrd"
    struct glist *next;
    struct glist *prev;
} gtpList;

gtpList *genListElement(char *concept,
                        char *sentence,
                        int timesUsed,
                        char *learnedFrom,
                        gtpList *head);

void swap(char *str1, char *str2);

char *readLine(FILE *fp);

char *readString(void);

void readFile(char *filePath, gtpList *head);

int parseStr(const char *str);

void splitStrings(char *source, char *concept, char *sentence, int split);

#endif // PROJECT2_CHATBOT_H
