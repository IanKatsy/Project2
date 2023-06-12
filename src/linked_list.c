#include "chatBot.h"
#include <string.h>
#include <stdlib.h>

gtpList *lastNode(gtpList *root) {

    while (root && root->next)
        root = root->next;

    return root;
}

gtpList *genListElement(char *concept,
                        char *sentence,
                        int timesUsed,
                        char *learnedFrom) {

    gtpList *new_ptr, *previous_ptr, *current_ptr;

    size_t size = sizeof(gtpList);
    new_ptr = malloc(size);

    if (new_ptr == NULL) {
        perror("malloc() returned a NULL pointer");
    }

    new_ptr->concept = strdup(concept);
    new_ptr->absolute_concept = strdup(concept);
    str_to_upper(new_ptr->absolute_concept);

    new_ptr->sentence = strdup(sentence);

    free(concept);
    free(sentence);

    new_ptr->timesUsed = timesUsed;
    strcpy(new_ptr->learnedFrom, learnedFrom);
    new_ptr->next = NULL;
    new_ptr->prev = NULL;

    previous_ptr = NULL;
    current_ptr = list_head;

    while (current_ptr != NULL &&
    compare_strings(new_ptr->absolute_concept,
                    current_ptr->absolute_concept) < 0
            ) {
        previous_ptr = current_ptr;
        current_ptr = current_ptr->next;
    }

    if (previous_ptr == NULL) {
        list_head = new_ptr;
    } else {
        previous_ptr->next = new_ptr;
        new_ptr->next = current_ptr;
    }

    return new_ptr;
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

        if (split == -1) {
            fprintf(stdout, "Format error in line %d!\n", line_count);
            fprintf(dialog, "Format error in line %d!\n", line_count);
            free(str);
            continue;
        }

        char *concept = NULL, *sentence = NULL;

        split_strings(str, &concept, &sentence, split);

        genListElement(concept, sentence, 0, LEARNED_FL);
    }

    fclose(fp);

    return 0;
}
