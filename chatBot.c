#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    gtpList listHead = {
            NULL,
            NULL,
            0,
            {0},
            NULL,
            NULL
    };

//    FILE *fp = fopen(WIKI_DEBUG, "r");
//
//    while (!feof(fp)) {
//        char *str = readLine(fp);
//        puts(str);
//        putc('\n', stdout);
//        free(str);
//    }

    readFile(WIKI_DEBUG);

    return 0;

}