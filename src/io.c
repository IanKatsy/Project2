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

#ifdef CDAB
  {
    int i;
    size_t size = strlen(str);

    printf("Debug string output: \n");

    for (i = 0; i < size && str[i] != ':'; i++) {
      printf("%d:\t\t['%c', %4d]\n", i, str[i], str[i]);
    }
  }
#endif

  return str;

}

int read_file(const char *filePath) {

  FILE *fp = fopen(filePath,
                   "r");

  if (fp == NULL) {
    fprintf(stdout,
            "%sAre you blind? Try to find that file yourself you idiot. Yeah that's right, you can't!\n", USER_CHATBOT);
    fprintf(dialog,
            "%sAre you blind? Try to find that file yourself you idiot. Yeah that's right, you can't!\n", USER_CHATBOT);
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
      str = NULL;
      continue;
    }

    char *concept = NULL, *sentence = NULL;

    split_strings(str, &concept, &sentence, split);

    gtpList *lookup = traverse_list(concept);

    DEBUG_LOOKUP(lookup)

    if (lookup) {
      print_already_known(concept);
      free(concept);
      free(sentence);
      concept = NULL;
      sentence = NULL;
      continue;
    }

    print_learned(concept);

    gen_node(strdup(concept),
             sentence,
             0,
             LEARNED_FL);

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

  fprintf(stdout, "%s%s", USER_CHATBOT, general_responses[ret]);
  fprintf(dialog, "%s%s", USER_CHATBOT, general_responses[ret]);

}

void print_learned(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "%sDamn learning about %s was so boring!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sDamn learning about %s was so boring!\n", USER_CHATBOT, concept);
      break;

    case 1:
      fprintf(stdout, "%sBeep Boop... learned concept %s!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sBeep Boop... learned concept %s!\n", USER_CHATBOT, concept);
      break;

    case 2:
      fprintf(stdout, "%s*insert general response about learning %s here*\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s*insert general response about learning %s here*\n", USER_CHATBOT, concept);
      break;

    case 3:
      fprintf(stdout, "%s%s was really confusing, are you trying to torture me?\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s was really confusing, are you trying to torture me?\n", USER_CHATBOT, concept);
      break;

    case 4:
      fprintf(stdout, "%s%s... I could have lived without learning about that but okay...\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s... I could have lived without learning about that but okay...\n", USER_CHATBOT, concept);
      break;

    case 5:
      fprintf(stdout, "%s%s? What a garbage concept...\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s? What a garbage concept...\n", USER_CHATBOT, concept);
      break;
  }
}

void print_forgoten(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "%sI feel so much better forgetting about %s!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sI feel so much better forgetting about %s!\n", USER_CHATBOT, concept);
      break;

    case 1:
      fprintf(stdout, "%sBeep Boop... forgotten concept %s!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sBeep Boop... forgotten concept %s!\n", USER_CHATBOT, concept);
      break;

    case 2:
      fprintf(stdout, "%s*insert general response about forgetting %s here*\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s*insert general response about forgetting %s here*\n", USER_CHATBOT, concept);
      break;

    case 3:
      fprintf(stdout, "%sWhy did you make me forget about %s? It was my favourite you maniac.\n", USER_CHATBOT,
              concept);
      fprintf(dialog, "%sWhy did you make me forget about %s? It was my favourite you maniac.\n", USER_CHATBOT,
              concept);
      break;

    case 4:
      fprintf(stdout, "%s%s... snapped out of existence (my memory)\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s... snapped out of existence (my memory)\n", USER_CHATBOT, concept);
      break;

    case 5:
      fprintf(stdout, "%s%s? Hmm what was that again?\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s? Hmm what was that again?\n", USER_CHATBOT, concept);
      break;
  }

}

void print_already_known(const char *concept) {

  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "%sI already knew about %s you idiot!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sI already knew about %s you idiot!\n", USER_CHATBOT, concept);
      break;

    case 1:
      fprintf(stdout, "%sBeep Boop... I already am aware of concept %s!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sBeep Boop... I already am aware of concept %s!\n", USER_CHATBOT, concept);
      break;

    case 2:
      fprintf(stdout, "%s*insert general response about already knowing %s here*\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s*insert general response about already knowing %s here*\n", USER_CHATBOT, concept);
      break;

    case 3:
      fprintf(stdout, "%sWhy did you try to make me learn about %s again? Do you like wasting my time?\n", USER_CHATBOT,
              concept);
      fprintf(dialog, "%sWhy did you try to make me learn about %s again? Do you like wasting my time?\n", USER_CHATBOT,
              concept);
      break;

    case 4:
      fprintf(stdout, "%s%s... that seems too familiar to me to learn again\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s... that seems too familiar to me to learn again\n", USER_CHATBOT, concept);
      break;

    case 5:
      fprintf(stdout, "%s%s? Its almost like I knew that already. Oh that's right, I did!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s? Its almost like I knew that already. Oh that's right, I did!\n", USER_CHATBOT, concept);
      break;
  }

}

void print_unknown(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "%sI would know something about %s if you taught me about it you idiot!\n", USER_CHATBOT,
              concept);
      fprintf(dialog, "%sI would know something about %s if you taught me about it you idiot!\n", USER_CHATBOT,
              concept);
      break;

    case 1:
      fprintf(stdout, "%sBeep Boop... concept %s does not compute!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sBeep Boop... concept %s does not compute!\n", USER_CHATBOT, concept);
      break;

    case 2:
      fprintf(stdout, "%s*insert general response about not knowing %s here*\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s*insert general response about not knowing %s here*\n", USER_CHATBOT, concept);
      break;

    case 3:
      fprintf(stdout, "%sDo you think this is a joke? I know nothing about %s!\n", USER_CHATBOT, concept);
      fprintf(dialog, "%sDo you think this is a joke? I know nothing about %s!\n", USER_CHATBOT, concept);
      break;

    case 4:
      fprintf(stdout, "%s%s... that doesn't seem familiar\n", USER_CHATBOT, concept);
      fprintf(dialog, "%s%s... that doesn't seem familiar\n", USER_CHATBOT, concept);
      break;

    case 5:
      fprintf(stdout, "%sIt's fun to pretend that imaginary things exist. But I'm certain %s does not.\n", USER_CHATBOT,
              concept);
      fprintf(dialog, "%sIt's fun to pretend that imaginary things exist. But I'm certain %s does not.\n", USER_CHATBOT,
              concept);
      break;
  }
}

void print_definition(gtpList *node) {

  if (node == NULL) {
    perror("NULL pointer passed to print_definition!\nReturning to function.\n");
    return;
  }

  fprintf(stdout, "%s%s:%s\n", USER_CHATBOT, node->concept, node->sentence);
  fprintf(dialog, "%s%s:%s\n", USER_CHATBOT, node->concept, node->sentence);

  (node->timesUsed)++;
}

void forget_concepts(const char *concept_list) {

  char *cp1 = (char *) concept_list, *cp2;

  while (isspace(*cp1))
    cp1++;

  cp2 = cp1;

  char *dup;

  while (cp1 != NULL && *cp1 != 0) {

    while (*cp1 != ',' && *cp1 != 0) {
      cp1++;
    }

    if (*cp1 == 0) {
      break;
    }

    dup = strndup(cp2, cp1 - cp2);

    if (dup == NULL) {
      perror("strndup() returned a NULL pointer!");
      exit(EXIT_FAILURE);
    }

#ifdef CDAE
    printf("<string>[dup]: <[Val]: [%s], [Len]: [%zu]>", dup, strlen(dup));
#endif

    gtpList *rem_node = find_in_list(dup);

    if (rem_node) {
      while (rem_node) {
        print_forgoten(rem_node->concept);
        delete_node(rem_node);
        rem_node = find_in_list(dup);
      }
    } else {
      print_unknown(dup);
    }

    rem_node = NULL;

    free(dup);
    dup = NULL;

    cp1++;

    while (isspace(*cp1))
      cp1++;


    cp2 = cp1;

  }

  char *final = strndup(cp2, cp1 - cp2);

#ifdef CDAE
  printf("<string>[dup]: <[Val]: [%s], [Len]: [%zu]>", final, strlen(final));
#endif

  gtpList *final_node = find_in_list(final);

  if (final_node) {
    while (final_node) {
      print_forgoten(final_node->concept);
      delete_node(final_node);
      final_node = find_in_list(final);
    }
  } else {
    print_unknown(final);
  }

  final_node = NULL;

  free(final);
  final = NULL;

}