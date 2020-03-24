/**
 * CS 2110 - Spring 2019 - Timed Lab 5
 *
 * Do not modify this file!
 *
 * struct tl5.h
 */

#ifndef tl5_H
#define tl5_H

#include <stdlib.h>

// This is just to remove compiler warnings associated with unused variables.
// Delete calls to this as you implement functions.
#define UNUSED_PARAMETER(x) (void)(x)

/**************************
 ** Datatype definitions **
 **************************/

/*
 * The following structs define the list and pokemon nodes for use in tl5.c. DO NOT MODIFY THESE STRUCT DEFINITIONS
 */

struct pokemon
{
    struct pokemon *evolve;
    int level;
    char* type;
};


struct list
{
    // Head pointer either points to a node with data or if the struct list is
    // empty NULL
    struct pokemon *starter_pokemon;
};

/***************************************************
** Prototypes for struct list library functions.  **
**                                                **
** For more details on their functionality,       **
** check tl5.c.                                   **
***************************************************/

/* Copy List */
struct list *copy_list(struct list *listToCopy);

/* Destroy List */
void destroy(struct list *listToDestroy);
#endif
