/*
    *   IOANNIS KATSIYIANNIS
    *   AM: 2022202200081
    *   Email:  dit22081@go.uop.gr
    *
    *   SOTIRIOS-ELEFTHERIOS DIMITROUSIS
    *   AM: 2022202100048
    *   Email: dit21048@go.uop.gr
*/

#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

#define SAVED_CONVERSATION "dialog.txt"

int main(void) {

    srand(time(NULL));

    char *message_get;

    FILE *dialog = fopen(SAVED_CONVERSATION, "w+");

    while (true) {

        fprintf(stdout, "%s", USER_USER);
        fprintf(dialog, "%s", USER_USER);

        message_get = read_string();

        int cmd = parse_command(message_get);

        switch (cmd) {

            case CASE_ALL_KNOWN:
                break;

            case CASE_PURE_PRINT:
                break;

            case CASE_LEARNED_FL:
                break;

            case CASE_LEARNED_KB:
                break;

            case CASE_FORGET:
                break;

            case CASE_GENERAL:
                break;

            case CASE_EXIT:
                break;

            case CASE_FORTY_TWO:
                fprintf(stdout, "%s 42\n", USER_CHATBOT);
                fprintf(dialog, "%s 42\n", USER_CHATBOT);
                break;

            default:
                break;

        }
    }

    fclose(dialog);
    return 0;

}
#pragma clang diagnostic pop