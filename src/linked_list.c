#include "chatBot.h"
#include <string.h>
#include <stdlib.h>

gtpList *last_node(gtpList *root) {

    while (root && root->next)
        root = root->next;

    return root;
}

void gen_node(char *concept, char *sentence, int timesUsed, char *learnedFrom) {
    gtpList *node = malloc(sizeof(gtpList));
    node->concept = strdup(concept);
    str_to_upper(concept);
    node->absolute_concept = strdup(concept);
    free(concept);
    node->sentence = strdup(sentence);
    free(sentence);
    node->timesUsed = timesUsed;
    strncpy(node->learnedFrom, learnedFrom, 5);
    node->next = NULL;
    node->prev = NULL;

    insert_and_sort(node);
}

void insert_and_sort(gtpList *node) {
    if (list_head == NULL) {
        // The list is empty, make the new node the head
        list_head = node;
        node->next = NULL;
        node->prev = NULL;
    } else {
        // Traverse the list to find the appropriate position to insert the node
        gtpList *current = list_head;
        while (current != NULL && strcmp(current->absolute_concept, node->absolute_concept) < 0) {
            current = current->next;
        }

        if (current == NULL) {
            // Insert at the end of the list
            gtpList *prev = list_head;
            while (prev->next != NULL) {
                prev = prev->next;
            }
            prev->next = node;
            node->prev = prev;
            node->next = NULL;
        } else if (current->prev == NULL) {
            // Insert at the beginning of the list
            node->next = current;
            current->prev = node;
            node->prev = NULL;
            list_head = node;
        } else {
            // Insert in the middle of the list
            node->next = current;
            node->prev = current->prev;
            current->prev->next = node;
            current->prev = node;
        }
    }
}

void delete_node(gtpList *node) {
    if (node == NULL) {
        return;
    }

    if (node == list_head) {
        // If the node is the head of the list
        list_head = node->next;
        if (list_head != NULL) {
            list_head->prev = NULL;
        }
    } else {
        // If the node is not the head of the list
        node->prev->next = node->next;
        if (node->next != NULL) {
            node->next->prev = node->prev;
        }
    }

    free(node->concept);
    free(node->sentence);
    free(node->absolute_concept);
    free(node);
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
