#include "chatBot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <ctype.h>

int parse_str(const char *str) {

  int i = 0;

  while (1) {
    if (*(str + i) == 0)
      return PARSE_ERROR;

    if (*(str + i) == ':') {

      if (*(str + i + 1) != ' ')
        return PARSE_ERROR;

      return i;
    }

    i++;
  }

}

void split_strings(char *source, char **concept, char **sentence, int split) {

  if (*concept != NULL || *sentence != NULL) {
    printf("concept or sentences aren't NULL");
  }

  size_t len = strlen(source);

  int i;

  char *get_concept = malloc(split + 1);

  if (get_concept == NULL) {
    perror("malloc() returned a NULL pointer!\n");
    exit(0);
  }

  *concept = get_concept;

  for (i = 0; i < split; i++) {
    get_concept[i] = source[i];
  }
  get_concept[split] = 0;

  size_t length = len - split;
  char *get_sentence = malloc(length + 1);

  if (get_sentence == NULL) {
    perror("malloc() returned a NULL pointer!\n");
    exit(0);
  }

  *sentence = get_sentence;

  for (i = 0; i < length; i++) {
    get_sentence[i] = source[i + split + 1];
  }
  get_sentence[length] = 0; // just in case

  free(source);

}

int parse_command(const char *cp, char **get_output, gtpList **get_data) {

  if (!strncmp(cp, COMMAND_LEARN_KB, strlen(COMMAND_LEARN_KB)))
    return CASE_LEARNED_KB;

  if (!strncmp(cp, COMMAND_LEARN_FL, strlen(COMMAND_LEARN_FL)))
    return CASE_LEARNED_FL;

  if (!strncmp(cp, COMMAND_FORGET, strlen(COMMAND_FORGET)))
    return CASE_FORGET;

  if (!strcasecmp(cp, COMMAND_LEAVE))
    return CASE_EXIT;

  if (!strcasecmp(cp, COMMAND_FORTY_TWO))
    return CASE_FORTY_TWO;

  if (!strcasecmp(cp, COMMAND_ALL_KNOWLEDGE))
    return CASE_ALL_KNOWN;

  if (!strcasecmp(cp, COMMAND_PURE_PRINT))
    return CASE_USED_IN_CONVO;

  size_t len = strlen(cp);

#ifdef CDAC
  {
    printf("cp[len - 1]: [len, %3zu] ['%c', %4d]\n", len, cp[len - 1], cp[len - 1]);
  }
#endif

  if (cp[len - 1] == '?') {

#ifdef CDAC
  {
    printf("Got in!\n");
  }
#endif

    extract_string(cp, get_output);

    if (*get_output == NULL) {
      return CASE_GENERAL;
    }

    gtpList *look = traverse_list(*get_output);

    if (look != NULL) {
      *get_data = look;
      return CASE_MAKE_CONVO;
    }

    gtpList *desperate = find_in_content(cp);

    if (desperate) {
      *get_data = desperate;
      return CASE_MAKE_CONVO;
    }

    return CASE_UNKNOWN;
  }

  return CASE_GENERAL;
}

void str_to_upper(char *string) {

  size_t len = strlen(string);
  int i;

  for (i = 0; i < len; i++) {
    if (isalpha(*(string + i))) {
      *(string + i) = (char) toupper(*(string + i));
    }
  }

}

void extract_string(const char *input, char **output) {
  const char *start = strchr(input, '*');  // Find the first asterisk
  const char *end = strrchr(input, '*');   // Find the last asterisk

  if (start == NULL || start == end) {
    *output = NULL;  // No asterisks found or only one asterisk
    return;
  }

  start++;  // Move past the first asterisk

  while (isspace(*start)) {
    start++;
  }

  while (end > start && isspace(*(end - 1))) {
    end--;
  }

  size_t length = end - start;
  *output = malloc((length + 1) * sizeof(char));
  strncpy(*output, start, length);
  *output[length] = '\0'; // just in case

}
