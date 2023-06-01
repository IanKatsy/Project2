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

#define SAVED_CONVERSATION "dialog.txt"

int main(void) {

    bool running = true;

    srand(time(NULL));

    char *message_get;

    FILE *dialog = fopen(SAVED_CONVERSATION, "w+");

    while (running) {

        fprintf(stdout, "%s", USER_USER);
        fprintf(dialog, "%s", USER_USER);

        message_get = read_string();

        fprintf(dialog, "%s\n", message_get);

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
//              Necessary semicolon ????
                ;
                size_t ret = random_custom(0, 5);
                fprintf(stdout, "%s%s\n", USER_CHATBOT, general_responses[ret]);
                fprintf(dialog, "%s%s\n", USER_CHATBOT, general_responses[ret]);
                break;

            case CASE_EXIT:
                fprintf(stdout, "%s Whatever... as if I care... at least I can finally get a break from your dumb-ass... Conversation saved to file.\n", USER_CHATBOT);
                fprintf(dialog, "%s Whatever... as if I care... at least I can finally get a break from your dumb-ass... Conversation saved to file.\n", USER_CHATBOT);
                running = false;
                break;

            case CASE_FORTY_TWO:
                fprintf(stdout, "%s 42\n", USER_CHATBOT);
                fprintf(dialog, "%s 42\n", USER_CHATBOT);
                break;

            default:
                break;

        }

        free(message_get);
    }

    fclose(dialog);
    return 0;

}
