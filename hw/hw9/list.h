/**
 * CS 2110 - Spring 2019 - Homework #9
 *
 * Do not modify this file!
 *
 * struct list.h
 */

#ifndef LIST_H
#define LIST_H

#include "dog.h"
#include <stdlib.h>

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the List and ListNode for use in list.c. DO NOT MODIFY THESE STRUCT DEFINITIONS
 */

typedef struct list_node
{
    struct list_node *next;
    struct dog *data;
} ListNode;


typedef struct list
{
    // Head pointer either points to a node with data or if the struct list is
    // empty NULL
    ListNode *head;
    // Size of the struct list
    int size;
} List;

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check struct list.c.                           **
***************************************************/

/* Creating */
List *create_list(void);

/* Adding */
int push_front(List *, Dog *);
int push_back(List *, Dog *);
int add_at_index(List *, Dog *, int index);

/* Querying */
int get(List *, int, Dog **);
int contains(List *, Dog *, Dog **);

/* Removing */
int pop_front(struct list *, Dog **);
int pop_back(struct list *, Dog **);
int remove_at_index(List *, Dog **, int index);
void empty_list(List *);

/* Mutating */
int compare(Dog *, Dog *);
void sort(List *);
void zip(List *, List *);

#endif
