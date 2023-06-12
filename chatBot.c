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
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define SAVED_CONVERSATION "dialog.txt"

int main(void) {

    bool running = true;

    srand(time(NULL));

    char *message_get;

    dialog = fopen(SAVED_CONVERSATION, "w+");

    while (running) {

        fprintf(stdout, "%s", USER_USER);
        fprintf(dialog, "%s", USER_USER);

        message_get = read_string();

        fprintf(dialog, "%s\n", message_get);

        int cmd = parse_command(message_get);

        switch (cmd) {

            case CASE_ALL_KNOWN:

                fprintf(stdout, "%s", USER_CHATBOT);
                fprintf(dialog, "%s", USER_CHATBOT);

                gtpList *list = list_head;
                while (list) {

                    // sentences start with ' ' on purpose
                    fprintf(stdout, "%s:%s\n",list->concept, list->sentence);
                    fprintf(dialog, "%s:%s\n",list->concept, list->sentence);

                    list = list->next;
                }
                break;

            case CASE_PURE_PRINT:
                break;

            case CASE_LEARNED_FL:

                ;
                const char *file_read = strdup(message_get + strlen(COMMAND_LEARN_FL));

                int status = read_file(file_read);

                if (status) {
                    break;
                }

                fprintf(stdout,
                        "%s read file: %s\n",
                        USER_CHATBOT,
                        file_read);

                fprintf(dialog,
                        "%s read file: %s\n",
                        USER_CHATBOT,
                        file_read);

                break;

            case CASE_LEARNED_KB:

                ;
                char *keyboard_read = strdup(message_get + strlen(COMMAND_LEARN_FL));

                char *concept = NULL, *sentence = NULL;


                int split = parse_str(keyboard_read);

                if (split == PARSE_ERROR) {
                    fprintf(stdout, "Input format error!\n");
                    fprintf(dialog, "Input format error!\n");
                }

                split_strings(keyboard_read, &concept, &sentence, split);

                gen_node(strdup(concept),
                         sentence,
                         0,
                         LEARNED_KB);

                gtpList *new = list_head;

                while (1) {

                    if (new == NULL) {
                        // TODO: added element not found in list, "throw" error
                        exit(DEBUG_EXIT);
                    }

                    if (!strcmp(new->concept, concept)) {
                        break;
                    }
                    new = new->next;
                }

                free(concept);

                fprintf(stdout,
                        "%s learned: %s\n",
                        USER_CHATBOT,
                        new->concept);

                fprintf(dialog,
                        "%s learned: %s\n",
                        USER_CHATBOT,
                        new->concept);

                break;

            case CASE_FORGET:
                break;

            case CASE_GENERAL:

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
