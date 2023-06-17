#ifndef PROJECT2_CHATBOT_H
#define PROJECT2_CHATBOT_H

#define _GNU_SOURCE // Used for strcasestr. If it doesn't work on pelopas we //TODO: remove

#define WIKI_DEBUG "../wikipedia_100.txt"

#define DEBUG_EXIT 42069

// #define CDAA //TODO: RM LATER
// #define CDAB //TODO: RM LATER
#define CDAC

#ifdef CDAA // -DCDA
#define DEBUG_LOOKUP(x) printf("Value %p was returned!\n", x);
#define DEBUG_PRINT_CMP(x, y, z) printf("CMP [ %s ],[ %s ] with a return of %d!\n", x, y, z);
#else
#define DEBUG_LOOKUP(x) ;
#define DEBUG_PRINT_CMP(x, y, z) ;
#endif

#define LEARNED_KB "kbrd"
#define LEARNED_FL "file"

#include <stdio.h>
#include <stdbool.h>

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
    CASE_USED_IN_CONVO,
    CASE_MAKE_CONVO,
    CASE_UNKNOWN
};

typedef struct glist {
    char *concept;          // the concept learned
    char *sentence;         // the sentence associated with the concept
    int timesUsed;          // no of times the concept was used to an answer
    char learnedFrom[5];    // learned either from "file" or "kbrd"
    struct glist *next;
    struct glist *prev;
    char *absolute_concept; // will be only used for sorting purposes
} gtpList;

extern FILE *dialog;

extern gtpList *list_head;

extern gtpList *search;

void insert_and_sort(gtpList *node);

void gen_node(char *concept, char *sentence, int timesUsed, char *learnedFrom);

char *read_line(FILE *fp);

char *read_string(void);

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

int read_file(const char *filePath);

#ifndef PARSE_VALUES
#define PARSE_VALUES

#define PARSE_ERROR (-1)
#endif

int parse_str(const char *str);

void split_strings(char *source, char **concept, char **sentence, int split);

int parse_command(const char *cp, char **get_output, gtpList **get_data);

int random_custom(int l_bound, int h_bound);

void str_to_upper(char *string);

void delete_node(gtpList *node);

gtpList *find_in_list(const char *abs_concept, bool release);

void print_general(void);

void print_learned(const char *concept);

void print_unknown(const char *concept);

void print_forgoten(const char *concept);

void print_already_know(char *concept);

void extract_string(const char *input, char **output);

gtpList *find_in_content(const char *abs_concept);

gtpList *traverse_list(const char *lookup_concept);

#endif // PROJECT2_CHATBOT_H
