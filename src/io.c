#include "chatBot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char *read_string(void) {

  char *str = NULL, *cp;
  char ch;
  int len = 0;

  bool whitespace_check = false;

  do {
    ch = getchar();

    if (ch == '\n' || ch == EOF) {
      ch = '\0';
    }

    if (isspace(ch)) {

      if (whitespace_check)
        continue;

      whitespace_check = true;
      ch = ' ';

    } else {
      whitespace_check = false;
    }

    len++;

    cp = realloc(str, len * sizeof(char));

    if (cp == NULL) {
      perror("realloc() returned a NULL pointer");
      exit(EXIT_FAILURE);
    }

    str = cp;

    str[len - 1] = ch;

  } while (ch != '\0');

  return str;
}


int read_file(const char *filePath) {

  FILE *fp = fopen(filePath,
                   "r");

  if (fp == NULL) {
    fprintf(stdout,
            "Are you blind? Try to find that file yourself you idiot. Yeah that's right, you can't!\n");
    fprintf(dialog,
            "Are you blind? Try to find that file yourself you idiot. Yeah that's right, you can't!!\n");
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

    bool is_found = find_in_list(concept, false);

    if (is_found) {

    }

    gen_node(concept, sentence, 0, LEARNED_FL);
  }

  fclose(fp);

  return 0;
}

void print_general(void) {

  const char *general_responses[] = {
          "That sounds like a plan.\n",
          "Good for you dude!\n",
          "Not like I care.\n",
          "Cool!\n",
          "Yeah ok, got it..\n",
          "Ok I get it!!! Are you always this annoying?\n"
  };

  int ret = random_custom(0, 5 + 1);

  fprintf(stdout, "%s", general_responses[ret]);
  fprintf(dialog, "%s", general_responses[ret]);

}

void print_learned(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "Damn learning about %s was so boring!\n", concept);
      fprintf(dialog, "Damn learning about %s was so boring!\n", concept);
      break;

    case 1:
      fprintf(stdout, "Beep Boop ... learned concept %s!\n", concept);
      fprintf(dialog, "Beep Boop ... learned concept %s!\n", concept);
      break;

    case 2:
      fprintf(stdout, "*insert general response about learning %s here*\n", concept);
      fprintf(dialog, "*insert general response about learning %s here*\n", concept);
      break;

    case 3:
      fprintf(stdout, "%s was really confusing, are you trying to torture me?\n", concept);
      fprintf(dialog, "%s was really confusing, are you trying to torture me?\n", concept);
      break;

    case 4:
      fprintf(stdout, "%s... I could have lived without learning about that but okay...\n", concept);
      fprintf(dialog, "%s... I could have lived without learning about that but okay...\n", concept);
      break;

    case 5:
      fprintf(stdout, "%s? What a garbage concept...\n", concept);
      fprintf(dialog, "%s? What a garbage concept...\n", concept);
      break;
  }
}

void print_forgoten(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "I feel so much better forgetting about %s!\n", concept);
      fprintf(dialog, "I feel so much better forgetting about %s!\n", concept);
      break;

    case 1:
      fprintf(stdout, "Beep Boop ... forgotten concept %s!\n", concept);
      fprintf(dialog, "Beep Boop ... forgotten concept %s!\n", concept);
      break;

    case 2:
      fprintf(stdout, "*insert general response about forgetting %s here*\n", concept);
      fprintf(dialog, "*insert general response about forgetting %s here*\n", concept);
      break;

    case 3:
      fprintf(stdout, "Why did you make me forget about %s? It was my favourite you maniac.\n", concept);
      fprintf(dialog, "Why did you make me forget about %s? It was my favourite you maniac.\n", concept);
      break;

    case 4:
      fprintf(stdout, "%s... snapped out of existence (my memory)\n", concept);
      fprintf(dialog, "%s... snapped out of existence (my memory)\n", concept);
      break;

    case 5:
      fprintf(stdout, "%s? Hmm what was that again?\n", concept);
      fprintf(dialog, "%s? Hmm what was that again?\n", concept);
      break;
  }

}

void print_knowledge(const char *concept) {

  int ret = random_custom(0, 5 + 1);

  char *dup = strdup(concept);

  str_to_upper(dup);

  bool is_in = find_in_list(dup, false);

  gtpList *runner = list_head;

  if (is_in) {
    while (runner) {

      if (!strcmp(runner->absolute_concept, concept)) {
        break;
      }

      runner = runner->next;
    }
  }

}