#include "chatBot.h"
#include <string.h>
#include <stdlib.h>

gtpList *lastNode(gtpList *root) {

    while (root && root->next)
        root = root->next;

    return root;
}

void swap(char *str1, char *str2) {
    char *temp = str1;
    str1 = str2;
    str2 = temp;
}

gtpList *genListElement(char *concept,
                        char *sentence,
                        int timesUsed,
                        char *learnedFrom,
                        gtpList *head) {

    if (head->next == NULL && head->prev == NULL && head->sentence == NULL && head->concept == NULL) {
        head->timesUsed = timesUsed;

        strcpy(head->concept, concept);
        strcpy(head->sentence, sentence);
        strcpy(head->learnedFrom, learnedFrom);

        return head;
    }

    gtpList *node = malloc(sizeof(gtpList));

    node->timesUsed = timesUsed;

    strcpy(node->concept, concept);
    strcpy(node->sentence, sentence);
    strcpy(node->learnedFrom, learnedFrom);

    gtpList *tail = lastNode(&head);

}

void readFile(char *filePath, gtpList *head) {

    FILE *fp = fopen(filePath, "r");
    char *str;

    while (!feof(fp)) {
        str = readLine(fp);
        int split = parseStr(str);

        if (split == -1) {
            printf("Format error in line:\n'%s'\n", str);
            free(str);
            continue;
        }

        char *concept = NULL, *sentence = NULL;

        splitStrings(str, concept, sentence, split);

        genListElement(concept, sentence, 0, LEARNED_FL, head);
    }

    fclose(fp);
}
