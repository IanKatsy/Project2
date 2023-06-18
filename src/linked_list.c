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

gtpList *find_in_list(const char *concept) {

  /*
   *
   * goes through all the list to find all concepts that
   *
   * have the concept string in them
   *
   * */

  gtpList *runner = list_head;

  while (runner) {

    char *cp = strcasestr(runner->concept, concept);

    if (cp)
      return runner;

    runner = runner->next;
  }

  return NULL;

}

gtpList *find_in_content(const char *abs_concept) {

  /*
   *
   * This function should only be called when search is NULL.
   * Due to that, we only move to the next pointer.
   * If it finds something on the sentence of a node, it will stop there.
   *
   * strcasestr is used and is available due to the definition of "_GNU_SOURCE" before including the string.h header
   *
   * */

  if (search != NULL || abs_concept == NULL) {
    return NULL;
  }

  search = list_head;

  while (search) {

#ifdef CDAD
    printf("strcasestr(<search-sentence[%s]>, <abs_concept, [%s]>)\n", search->sentence, abs_concept);
#endif

    char *cp = strcasestr(search->sentence, abs_concept);

    if (cp) {
      return search;
    }

    search = search->next;

  }

  return NULL;
}

gtpList *traverse_list(const char *lookup_concept) {

  if (lookup_concept == NULL) {
    return NULL;
  }

  if (search == NULL) {
    search = list_head;
  }

  int result = 1;

  if (search != NULL) {

    result = strcasecmp(search->absolute_concept, lookup_concept);

    if (result == 0) {
      DEBUG_PRINT_CMP(search->absolute_concept, lookup_concept, result)
      return search;

    } else if (result > 0) {
      while (result > 0 && search != NULL) {
        search = search->prev; // Move to previous node, absolute concept of search is "bigger" in ascii

        if (search == NULL) {
          break;
        }

        result = strcasecmp(search->absolute_concept, lookup_concept);
        DEBUG_PRINT_CMP(search->absolute_concept, lookup_concept, result)
      }

    } else {
      while (result < 0 && search != NULL) {
        search = search->next; // Move to next node, absolute concept of search is "smaller" in ascii

        if (search == NULL) {
          break;
        }

        result = strcasecmp(search->absolute_concept, lookup_concept);
        DEBUG_PRINT_CMP(search->absolute_concept, lookup_concept, result)
      }
    }

  }

  if (result == 0) {
    return search;
  }

  return NULL;
}
