/**
 * CS 2110 - Spring 2019 - Homework #9
 *
 * @author Molly Williams
 *
 * list.c: Complete the functions!
 */

/**
 * !!!!!!!!!!!!!!!!!!!!!!!!!!!!-IMPORTANT-!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 * For any function that must use malloc, if malloc returns NULL, the function
 * itself should return NULL if needs to return something (or return 0 if
 * the function returns a int).
 */

// Do not add ANY additional includes!!!
#include "list.h"

/* You should NOT have any global variables. */

/* The create_node function is static because this is the only file that should
   have knowledge about the nodes backing the linked List. */
static inline ListNode *create_node(Dog *data);

/** create_node
  *
  * Helper function that creates a ListNode by allocating memory for it on the heap.
  * Be sure to set its next pointer to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @param data a void pointer to data the user wants to store in List
  * @return a ListNode
  */
static ListNode* create_node(Dog *data)
{
    ListNode *head;
    head = malloc(sizeof(ListNode));
    if (head == NULL) {
      return NULL;
    }
    head->data = data;
    head->next = NULL;
    //UNUSED_PARAMETER(data);
    return head;
}

/** create_list
  *
  * Creates a struct list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head to NULL.
  *
  * If malloc returns NULL, you should return NULL to indicate failure.
  *
  * @return a pointer to a new struct list or NULL on failure
  */
List *create_list(void)
{
    List *linkedlist;
    linkedlist = malloc(sizeof(List));
    if (linkedlist == NULL) {
      return NULL;
    }
    linkedlist->head = NULL;
    linkedlist->size = 0;
    return linkedlist;
}

/** push_front
  *
  * Adds the element at the front of the struct list.
  *
  * @param listToPrependTo a pointer to the struct list structure.
  * @param data the data to add to the struct list.
  * @return 0 if the struct list is NULL, 1 if successful.
  */
int push_front(List *listToPrependTo, Dog *data)
{
    //UNUSED_PARAMETER(listToPrependTo);
    //UNUSED_PARAMETER(data);
    if (listToPrependTo == NULL) {
      return 0;
    }
    ListNode *new;
    new = create_node(data);
    new->next = listToPrependTo->head;
    listToPrependTo->head = new;
    int currentSize = listToPrependTo->size;
    currentSize = currentSize + 1;
    listToPrependTo->size = currentSize;
     return 1;
}

/** push_back
  *
  * Adds the element to the back of the List.
  *
  * @param listToAppendTo a pointer to the List structure.
  * @param data the data to add to the List.
  * @return 0 if the List is NULL, 1 if successful.
  */
int push_back(List *listToAppendTo, Dog *data)
{
    // UNUSED_PARAMETER(listToAppendTo);
    // UNUSED_PARAMETER(data);
    if (listToAppendTo == NULL) {
      return 0;
    }
    ListNode *cursor = listToAppendTo->head;
    if (cursor == NULL) {
      ListNode *new_node;
      new_node = create_node(data);
      listToAppendTo->head = new_node;
    } else {
      while(cursor->next != NULL) {
        cursor = cursor->next;
      }
    ListNode *new_node;
    new_node = create_node(data);
    cursor->next = new_node;
  }
    int currentSize = listToAppendTo->size;
    currentSize = currentSize + 1;
    listToAppendTo->size = currentSize;
    return 1;
}

/** add_at_index
  *
  * Add the element at the specified index in the List. This index must lie in
  * the inclusive range [0,size].
  * For example, if you have no elements in the List,
  * you should be able to add to index 0 but no further.
  * If you have two elements in the List,
  * you should be able to add to index 2 but no further.
  *
  * @param listToAddTo a pointer to the List structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the List
  * @return 0 if the index is out of bounds or the List is NULL
  *         (do not add the data in this case)
  *         otherwise return 1
  */
int add_at_index(List *listToAddTo, Dog *data, int index)
{
    // UNUSED_PARAMETER(listToAddTo);
    // UNUSED_PARAMETER(data);
    // UNUSED_PARAMETER(index);
  if (listToAddTo == NULL) {
    return 0;
  }
  if (index < 0 || index > listToAddTo->size) {
    return 0;
  }
  ListNode *cursor = listToAddTo->head;
  if (cursor == NULL) {
    ListNode *new_node;
    new_node = create_node(data);
    listToAddTo->head = new_node;
  } else {
  int count = 0;
    while(count != index - 1) {
        cursor = cursor->next;
        count++;
      }
    ListNode *new_node;
    new_node = create_node(data);
    new_node->next = cursor->next;
    cursor->next = new_node;
  }
    int currentSize = listToAddTo->size;
    currentSize = currentSize + 1;
    listToAddTo->size = currentSize;
    return 1;
}

/** get
  *
  * Gets the data at the specified index in the List
  *
  * @param listToGetDataFrom a pointer to the List structure
  * @param index 0-based, starting from the head.
  * @param dataOut A pointer to a pointer used to return the data from the
  *        specified index in the List or NULL on failure.
  * @return 0 if dataOut is NULL or index is out of range of the List or
  *         the List is NULL, 1 otherwise
  */
int get(List *listToGetDataFrom, int index, Dog **dataOut)
{
    // UNUSED_PARAMETER(listToGetDataFrom);
    // UNUSED_PARAMETER(index);
    // UNUSED_PARAMETER(dataOut);
  if (listToGetDataFrom == NULL || dataOut == NULL) {
      return 0;
    }
    if (index < 0 || index > listToGetDataFrom->size-1) {
      return 0;
    }
    ListNode *cursor = listToGetDataFrom->head;
    int count = 0;
    while(count != index) {
        cursor = cursor->next;
        count++;
      }
    *dataOut = cursor->data;
    return 1;
}

/** contains
  *
  * Traverses the List, trying to see if the List contains some
  * data. We will consider a node to contain the same data if the dog at that
  * node has the same name as the dog passed in.
  *
  * The "data" parameter may not necessarily point to the same address as the
  * equal data you are returning from this function, it's just data which the
  * comparator (dog_eq_name in this case) says is equal.
  *
  * If there are multiple pieces of data in the List which are equal to
  * the "data" parameter, return the one at the lowest index.
  *
  * Use dog_eq_name to compare dog structs. Be sure to take a look at that
  * function before you use it! Also be sure not to use dog_eq.
  *
  * @param listToSearch a pointer to the List structure
  * @param data The data, to see if it exists in the List
  * @param dataOut A pointer to a pointer used to return the data contained in
  *                the List or NULL on failure
  * @return int    0 if dataOut is NULL, the list is NULL, or the list
  *                does not contain data, else 1
  */
int contains(List *listToSearch, Dog *data, Dog **dataOut)
{
    // UNUSED_PARAMETER(listToSearch);
    // UNUSED_PARAMETER(data);
    // UNUSED_PARAMETER(dataOut);
    if (listToSearch == NULL || dataOut == NULL) {
      return 0;
    }
    if (listToSearch->size == 0) {
      *dataOut = NULL;
      return 0;
    }
    ListNode *cursor = listToSearch->head;
    while(cursor != NULL) {
        if (dog_eq_name(data, cursor->data) == 0) {
          *dataOut = cursor->data;
          return 1;
        }
        cursor = cursor->next;
      }
    *dataOut = NULL;
    return 0;

}

/** pop_front
  *
  * Removes the List_node at the front of the List, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the List.
  * @param dataOut A pointer to a pointer used to return the data in the first
  *                List_node or NULL on failure
  * @return 0 if dataOut is NULL or the List is NULL or empty, else 1
  */
int pop_front(List *listToPopFrom, Dog **dataOut)
{
    // UNUSED_PARAMETER(listToPopFrom);
    // UNUSED_PARAMETER(dataOut);
    if (dataOut == NULL || listToPopFrom == NULL || listToPopFrom->size == 0) {
      return 0;
    }
    ListNode *toReturn = listToPopFrom->head;
    *dataOut = toReturn->data;
    ListNode *next = listToPopFrom->head;
    next = next->next;
    listToPopFrom->head = next;
    int currentSize = listToPopFrom->size;
    currentSize = currentSize - 1;
    listToPopFrom->size = currentSize;
    free(toReturn);
    return 1;
}

/** pop_back
  *
  * Removes the ListNode at the back of the List, and returns its data to the user
  *
  * @param listToPopFrom a pointer to the List.
  * @param dataOut A pointer to a pointer used to return the data in the last
  *                ListNode or NULL on failure
  * @return 0 if dataOut is NULL or the List is NULL or empty, else 1
  */
int pop_back(List *listToPopFrom, Dog **dataOut)
{
    // UNUSED_PARAMETER(listToPopFrom);
    // UNUSED_PARAMETER(dataOut);
    if (dataOut == NULL || listToPopFrom == NULL || listToPopFrom->size == 0) {
      return 0;
    }
    ListNode *cursor = listToPopFrom->head;
    ListNode *toReturn;
    if (listToPopFrom->size == 1) {
      *dataOut = cursor->data;
      listToPopFrom->head = NULL;
      free(cursor);
    } else {
      while (cursor->next->next != NULL) {
        cursor = cursor->next;
      }
      toReturn = cursor->next;
      *dataOut = toReturn->data;
      cursor->next = NULL;
      free(toReturn);
    }
    // int count = 0;
    //   while(count < listToPopFrom->size-1) {
    //     cursor = cursor->next;
    //     count++;
    //   }
    int currentSize = listToPopFrom->size;
    currentSize = currentSize - 1;
    listToPopFrom->size = currentSize;
    return 1;
}


/** remove_at_index
  *
  * Remove the element at the specified index in the List.
  *
  * @param listToAddTo a pointer to the List structure
  * @param index 0-based, starting from the head in the inclusive range
  *              [0,size]
  * @param data the data to add to the List
  * @return 0 if the index is out of bounds, the List is NULL or
  *         the dataOut is NULL
  *         otherwise return 1
  */
int remove_at_index(List * listToRemoveFrom, Dog ** dataOut, int index)
{
    // UNUSED_PARAMETER(listToRemoveFrom);
    // UNUSED_PARAMETER(dataOut);
    // UNUSED_PARAMETER(index);
    if (listToRemoveFrom == NULL || dataOut == NULL || listToRemoveFrom->size == 0) {
      return 0;
    }
    if (index < 0 || index>=listToRemoveFrom->size) {
      return 0;
    }
    int count = 0;
    ListNode *cursor = listToRemoveFrom->head;
    if (index == 0) {
      return pop_front(listToRemoveFrom, dataOut);
    } else {
    while (count < index - 1) {
      cursor = cursor->next;
      count++;
    }
    ListNode *toReturn = cursor->next;
    *dataOut = toReturn->data;
    cursor->next = toReturn->next;
    free(toReturn);
    int currentSize = listToRemoveFrom->size;
    currentSize = currentSize - 1;
    listToRemoveFrom->size = currentSize;
  }
    return 1;
}

/** empty_list
  *
  * Empties the List. After this is called, the List should be
  * empty. This does not free the List struct itself, just all nodes and
  * data within. Make sure to check that listToEmpty is not NULL before
  * using it.
  *
  * Call dog_free to free a dog struct.
  *
  * @param listToEmpty a pointer to the List structure
  */
void empty_list(List *listToEmpty)
{
    //UNUSED_PARAMETER(listToEmpty);
    if (listToEmpty == NULL) {
      return;
    }
    ListNode *current = listToEmpty->head;
    ListNode *nextElement;
    //ListNode *nextElement = current->next;
    while (current != NULL) {
      nextElement = current->next;
      dog_free(current->data);
      free(current);
      current = nextElement;
      //nextElement = nextElement->next;
    }
    listToEmpty->size = 0;
}

/** zip
  *
  *
  * Zips two Lists together. After this is called, the first list should
  * have the elements from both lists and the second list should be empty.
  * Do not free the second list. Both Lists might be empty. If either list
  * is NULL, just return.
  *
  *     List *A: A1 -> A2 -> A3 -> A4 -> A5 -> NULL
  *
  *     List *B: B1 -> B2 -> B3 -> NULL
  *
  *     zip(A, B): A1 -> B1 -> A2 -> B2 -> A3 -> B3 -> A4 -> A5 -> NULL
  *
  * @param doggos first List to zip together
  * @param puppers second List to zip together
  */
void zip(List *doggos, List *puppers)
{
    // UNUSED_PARAMETER(doggos);
    // UNUSED_PARAMETER(puppers);
    if (doggos == NULL || puppers == NULL) {
      return;
    }
    if (doggos->size == 0 && puppers->size == 0) {
      return;
    }
    if (doggos->size == 0) {
      doggos->head = puppers->head;
      doggos->size = puppers->size;
      puppers->head = NULL;
    puppers->size = 0;
    return;
    }
    if (puppers->size == 0) {
      return;
    }
    ListNode *list1 = doggos->head;
    ListNode *list2 = puppers->head;
    ListNode *nextDog = list1->next;
    ListNode *nextPup = list2->next;
    while (list1 != NULL || list2 != NULL) {
      if (list1->next == NULL) {
        while (list2 != NULL) {
          push_back(doggos, list2->data);
          list1 = list1->next;
          list2 = list2->next;
        }
        list1 = list1->next;
      }
      else if (list1 != NULL) {
        if (list2 != NULL) {
          nextDog = list1->next;
          nextPup = list2->next;
          list1->next = list2;
          list2->next = nextDog;
          list1 = nextDog;
          list2 = nextPup;
        } else {
          list1 = list1->next;
        }
      }

    }
    doggos->size = doggos->size + puppers->size -1;
    puppers->head = NULL;
    puppers->size = 0;
}

/** sort
  *
  * Sorts the ListNodes of a List into a predefined order using the dog_compare
  * (compares ages) method. List will not be NULL but may be empty. You can use
  * whatever sorting algorithm you prefer, but we recommend using Insertion Sort.
  *
  *     List *A: A1 -> A4 -> A5 -> A2 -> A3 -> NULL
  *
  *     sort(A): A1 -> A2 -> A3 -> A4 -> A5 -> NULL
  *
  * @param borks: List to be sorted
  */
void sort(List *borkers)
{
    UNUSED_PARAMETER(borkers);
}
