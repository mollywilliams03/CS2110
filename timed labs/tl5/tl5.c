/**
 * CS 2110 - Spring 2019 - Timed Lab #5
 *
 * @author Molly Williams
 *
 * tl5.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl5.h"
#include "string.h"

///* You should NOT have any global variables. */


/** copy_list
  *
  * Create a new list and new pokemon nodes
  *
  * If listToCopy is NULL return NULL. For any memory allocations
  * failures your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must destroy
  * the list
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The struct list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
struct list *copy_list(struct list *listToCopy)
{
    //UNUSED_PARAMETER(listToCopy);
    if (listToCopy == NULL) {
      return NULL;
    }
    struct list *newlist = malloc(sizeof(struct list));
    if (newlist == NULL) {
      return NULL;
    }

    newlist->starter_pokemon = NULL;
    struct pokemon *curr = listToCopy->starter_pokemon;
    //struct pokemon *newCurr = newlist->starter_pokemon;
    if (curr == NULL) {
      return newlist;
    }
    while (curr != NULL) {
      struct pokemon *result = malloc(sizeof(struct pokemon));
      if (result == NULL) {
        destroy(newlist);
        return NULL;
      }
      if (newlist->starter_pokemon == NULL) {
        newlist->starter_pokemon = result;
      }
      result->type = malloc(strlen(curr->type) + 1);
      if (result->type == NULL) {
        free(result);
        destroy(newlist);
        return NULL;
      }
      strcpy(result->type, curr->type);
      result->evolve = NULL;
      result->level = curr->level;
      struct pokemon *cursor = newlist->starter_pokemon;
      while(cursor->evolve != NULL) {
          cursor = cursor->evolve;
        }
      if (cursor != result) {
        cursor->evolve = result;
      }
      curr = curr->evolve;
    }
    return newlist;
}

/** Destroy
  *
  * Destroys the entire struct list. This function removes every list node
  * and finally remove the list itself.
  *
  * HINT: remember every malloc needs a respective free
  *
  * @param listToEmpty a pointer to the struct list
  */
void destroy(struct list *listToDestroy)
{
    //UNUSED_PARAMETER(listToDestroy);
    if (listToDestroy == NULL) {
      return;
    }
    struct pokemon *curr = listToDestroy->starter_pokemon;
    struct pokemon *next;
    while (curr!= NULL) {
      next = curr->evolve;
      curr->level = 0;
      free(curr->type);
      free(curr);
      curr = next;
    }
    free(listToDestroy);
}

    // while (current != NULL) {
    //   nextElement = current->next;
    //   dog_free(current->data);
    //   free(current);
    //   current = nextElement;
    //   //nextElement = nextElement->next;
    // }

