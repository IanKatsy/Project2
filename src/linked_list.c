#include "chatBot.h"
#include <string.h>
#include <stdlib.h>

gtpList *last_node(gtpList *root) {

  while (root && root->next)
    root = root->next;

  return root;
}

void gen_node(char *concept, char *sentence, int timesUsed, char *learnedFrom) {
  gtpList *node = malloc(sizeof(gtpList));
  node->concept = strdup(concept);
  str_to_upper(concept);
  node->absolute_concept = strdup(concept);
  free(concept);
  node->sentence = strdup(sentence);
  free(sentence);
  node->timesUsed = timesUsed;
  strncpy(node->learnedFrom, learnedFrom, 5);
  node->next = NULL;
  node->prev = NULL;

  insert_and_sort(node);
}

void insert_and_sort(gtpList *node) {
  if (list_head == NULL) {
    // The list is empty, make the new node the head
    list_head = node;
    node->next = NULL;
    node->prev = NULL;
  } else {
    // Traverse the list to find the appropriate position to insert the node
    gtpList *current = list_head;

    while (current != NULL && strcmp(current->absolute_concept, node->absolute_concept) < 0) {
      current = current->next;
    }

    if (current == NULL) {
      // Insert at the end of the list
      gtpList *prev = list_head;
      while (prev->next != NULL) {
        prev = prev->next;
      }
      prev->next = node;
      node->prev = prev;
      node->next = NULL;
    } else if (current->prev == NULL) {
      // Insert at the beginning of the list
      node->next = current;
      current->prev = node;
      node->prev = NULL;
      list_head = node;
    } else {
      // Insert in the middle of the list
      node->next = current;
      node->prev = current->prev;
      current->prev->next = node;
      current->prev = node;
    }
  }
}

void delete_node(gtpList *node) {
  if (node == NULL) {
    return;
  }

  if (node == list_head) {

    list_head = node->next;

    if (list_head != NULL) {
      list_head->prev = NULL;
    }

  } else {

    node->prev->next = node->next;

    if (node->next != NULL) {
      node->next->prev = node->prev;
    }

  }

  free(node->concept);
  free(node->sentence);
  free(node->absolute_concept);
  free(node);
}

bool find_in_list(const char *abs_concept, bool release) {
  gtpList *runner = list_head;

  while (runner) {
    if (!strcasecmp(abs_concept, runner->absolute_concept)) {

      if (release) {
        free((void *) abs_concept);
      }

      return true;
    }

    runner = runner->next;
  }

  if (release) {
    free((void *) abs_concept);
  }

  return false;
}

bool traverse_list(const char *abs_concept) {

  if (search == NULL) {
    search = list_head;
  }

  int cmp = strcasecmp(search->absolute_concept, abs_concept);

  if (cmp < 0) {
    while (search != NULL && strcasecmp(search->absolute_concept, abs_concept) < 0)
      search = search->next;

    if (search == NULL) {
      return false;
    }

  } else if (cmp > 0) {
    while (search != NULL && strcasecmp(search->absolute_concept, abs_concept) > 0)
      search = search->prev;

    if (search == NULL) {
      return false;
    }

  } else {
    return true;
  }

  return false;
}
