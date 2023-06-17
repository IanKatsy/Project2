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

void do_nothing() {}

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

    char *get_string = NULL;
    gtpList *get_data = NULL;

    int cmd = parse_command(message_get, &get_string, &get_data);

    switch (cmd) {

      case CASE_ALL_KNOWN:

        do_nothing();
        fprintf(stdout, "%s", USER_CHATBOT);
        fprintf(dialog, "%s", USER_CHATBOT);

        gtpList *list = list_head;
        while (list) {

          // sentences start with ' ' on purpose
          fprintf(stdout, "%s:%s\n", list->concept, list->sentence);
          fprintf(dialog, "%s:%s\n", list->concept, list->sentence);

          list = list->next;
        }
        break;

      case CASE_USED_IN_CONVO:
        do_nothing();

        gtpList *i_am_starting_to_get_depressed = list_head;
        while (i_am_starting_to_get_depressed) {

          if (i_am_starting_to_get_depressed->timesUsed) {
            fprintf(stdout, "%s, used %d times\n",
                    i_am_starting_to_get_depressed->concept,
                    i_am_starting_to_get_depressed->timesUsed);
            fprintf(dialog, "%s, used %d times\n",
                    i_am_starting_to_get_depressed->concept,
                    i_am_starting_to_get_depressed->timesUsed);
          }

          i_am_starting_to_get_depressed = i_am_starting_to_get_depressed->next;
        }

        break;

      case CASE_LEARNED_FL:

        do_nothing();
        const char *file_read = strdup(message_get + strlen(COMMAND_LEARN_FL));

        int status = read_file(file_read);

        if (status) {
          break;
        }

        fprintf(stdout,
                "%s Beep Boop, I consumed the bytes out of %s. They were very spicy!\n",
                USER_CHATBOT,
                file_read);

        fprintf(dialog,
                "%s Beep Boop, I consumed the bytes out of %s. They were very spicy!\n",
                USER_CHATBOT,
                file_read);

        break;

      case CASE_LEARNED_KB:

        do_nothing();
        char *keyboard_read = strdup(message_get + strlen(COMMAND_LEARN_FL) + 1);

        char *concept = NULL, *sentence = NULL;

        int split = parse_str(keyboard_read);

        if (split == PARSE_ERROR) {
          fprintf(stdout, "Input format error!\n");
          fprintf(dialog, "Input format error!\n");
          break;
        }

        split_strings(keyboard_read, &concept, &sentence, split); // keyboard read gets freed in func

        gtpList *lookup = traverse_list(concept);

        DEBUG_LOOKUP(lookup)

        if (lookup) {
          print_already_know(concept);
          free(concept);
          free(sentence);
          break;
        }

        gen_node(strdup(concept),
                 sentence,
                 0,
                 LEARNED_KB);

        fprintf(stdout,
                "%s learned: %s\n",
                USER_CHATBOT,
                concept);

        fprintf(dialog,
                "%s learned: %s\n",
                USER_CHATBOT,
                concept);

        free(concept);

        break;

      case CASE_FORGET:

        do_nothing();
        char *to_delete = strdup(message_get + strlen(COMMAND_FORGET));

        str_to_upper(to_delete);



        break;

      case CASE_GENERAL:

        do_nothing();
        print_general();

        break;

      case CASE_EXIT:
        // TODO: haha funny joek
        do_nothing();
        fprintf(stdout,
                "%s So long, gay bowser!\n",
                USER_CHATBOT);
        fprintf(dialog,
                "%s So long, gay bowser!\n",
                USER_CHATBOT);
        running = false;
        break;

      case CASE_FORTY_TWO:

        do_nothing();
        fprintf(stdout, "%s 42\n", USER_CHATBOT);
        fprintf(dialog, "%s 42\n", USER_CHATBOT);
        break;

      case CASE_UNKNOWN:
        do_nothing();

        print_unknown(get_string);
        { free(get_string); }
        

        break;

      default:
        perror("What?");
        break;

    }

    free(message_get);
  }

  fclose(dialog);
  return 0;

}
