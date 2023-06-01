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

    if (list_head.concept != NULL) {
        gtpList *ret = malloc(sizeof(gtpList));

        ret->concept = concept;
        ret->sentence = sentence;
        ret->timesUsed = timesUsed;
        strcpy(ret->learnedFrom, learnedFrom);

        return ret;

    }

    list_head.concept = concept;
    list_head.sentence = sentence;
    list_head.timesUsed = timesUsed;
    strcpy(list_head.learnedFrom, learnedFrom);

    return &list_head;
}

gtpList *copy_list_element(gtpList cp) {

    size_t size = sizeof cp;

    gtpList *ret = malloc(size);

    memcpy(ret, &cp, size);

    return ret;
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

//        genListElement(concept, sentence, 0, LEARNED_FL, head);
    }

    fclose(fp);
}
