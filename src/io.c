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

void print_already_known(const char *concept) {

  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "I already knew about %s you idiot!\n", concept);
      fprintf(dialog, "I already knew about %s you idiot!\n", concept);
      break;

    case 1:
      fprintf(stdout, "Beep Boop ... I already am aware of concept %s!\n", concept);
      fprintf(dialog, "Beep Boop ... I already am aware of concept %s!\n", concept);
      break;

    case 2:
      fprintf(stdout, "*insert general response about already knowing %s here*\n", concept);
      fprintf(dialog, "*insert general response about already knowing %s here*\n", concept);
      break;

    case 3:
      fprintf(stdout, "Why did you try to make me learn about %s again? Do you like wasting my time?\n", concept);
      fprintf(dialog, "Why did you try to make me learn about %s again? Do you like wasting my time?\n", concept);
      break;

    case 4:
      fprintf(stdout, "%s... that seems too familiar to me to learn again\n", concept);
      fprintf(dialog, "%s... that seems too familiar to me to learn again\n", concept);
      break;

    case 5:
      fprintf(stdout, "%s? Its almost like I knew that already. Oh that's right, I did!\n", concept);
      fprintf(dialog, "%s? Its almost like I knew that already. Oh that's right, I did!\n", concept);
      break;
  }

}

void print_unknown(const char *concept) {
  int ret = random_custom(0, 5 + 1);

  switch (ret) {
    case 0:
      fprintf(stdout, "I would know something about %s if you taught you idiot!\n", concept);
      fprintf(dialog, "I would know something about %s if you taught you idiot!\n", concept);
      break;

    case 1:
      fprintf(stdout, "Beep Boop ... concept %s does not compute!\n", concept);
      fprintf(dialog, "Beep Boop ... concept %s does not compute!\n", concept);
      break;

    case 2:
      fprintf(stdout, "*insert general response about not knowing %s here*\n", concept);
      fprintf(dialog, "*insert general response about not knowing %s here*\n", concept);
      break;

    case 3:
      fprintf(stdout, "Do you think this is a joke? I know nothing about %s!\n", concept);
      fprintf(dialog, "Do you think this is a joke? I know nothing about %s!\n", concept);
      break;

    case 4:
      fprintf(stdout, "%s... that doesn't seem familiar\n", concept);
      fprintf(dialog, "%s... that doesn't seem familiar\n", concept);
      break;

    case 5:
      fprintf(stdout, "%s? It's fun to pretend that imaginary things exist. But I'm certain this does not.\n", concept);
      fprintf(dialog, "%s? It's fun to pretend that imaginary things exist. But I'm certain this does not.\n", concept);
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