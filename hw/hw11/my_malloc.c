/*
 * CS 2110 Spring 2019
 * Author: Molly Williams
 */

/* we need this for uintptr_t */
#include <stdint.h>
/* we need this for memcpy/memset */
#include <string.h>
/* we need this to print out stuff*/
#include <stdio.h>
/* we need this for the metadata_t struct and my_malloc_err enum definitions */
#include "my_malloc.h"
/* include this for any boolean methods */
#include <stdbool.h>

/*Function Headers
 * Here is a place to put all of your function headers
 * Remember to declare them as static
 */
static void setCanary(metadata_t* block);
static metadata_t* split(metadata_t* block, size_t size);
static void addToFreeList (metadata_t* mem);
static void removeFromFreeList(metadata_t* block);
static metadata_t* find_right(metadata_t* right);
static metadata_t* find_left(metadata_t* left);
static void merge(metadata_t* left, metadata_t* right);

/* Our freelist structure - our freelist is represented as a singly linked list
 * the size_list orders the free blocks by size in ascending order
 */

metadata_t *size_list;

/* Set on every invocation of my_malloc()/my_free()/my_realloc()/
 * my_calloc() to indicate success or the type of failure. See
 * the definition of the my_malloc_err enum in my_malloc.h for details.
 * Similar to errno(3).
 */
enum my_malloc_err my_malloc_errno;

/* MALLOC
 * See PDF for documentation
 */
void *my_malloc(size_t size) {
    if (size > SBRK_SIZE - TOTAL_METADATA_SIZE) {
        my_malloc_errno = SINGLE_REQUEST_TOO_LARGE;
        return NULL;
    }
    if (size == 0) {
        my_malloc_errno = NO_ERROR;
        return NULL;
    }

    metadata_t* curr = size_list;
    while(curr != NULL) {
        if (curr->size == (size)) {
            my_malloc_errno = NO_ERROR;
            removeFromFreeList(curr);
            setCanary(curr);
            curr->next = NULL;
            return (void*) (curr + 1);
        }
        else if (curr->size >= (size + MIN_BLOCK_SIZE)) {
            my_malloc_errno = NO_ERROR;
            curr = split(curr, (size + TOTAL_METADATA_SIZE));
            //make sure u are casting to a uint8_t * before adding the total size
            setCanary(curr);
            curr->next = NULL;
            return (void*) (curr + 1);
        }
        curr = curr->next;
    }
    if (curr == NULL) {
        metadata_t* newMem = my_sbrk(SBRK_SIZE);
        if (newMem == NULL) {
            my_malloc_errno = OUT_OF_MEMORY;
            return NULL;
        }
        my_malloc_errno = NO_ERROR;
        newMem->size = SBRK_SIZE - TOTAL_METADATA_SIZE;
        newMem->next = NULL;
        metadata_t* leftFound = find_left(newMem);
        metadata_t* rightFound = find_right(newMem);
        if (leftFound != NULL && rightFound == NULL) {
            merge(leftFound, newMem);
            addToFreeList(leftFound);
        }
         else if (rightFound != NULL && leftFound == NULL) {
            merge(newMem, rightFound);
            addToFreeList(newMem);
        }
    else if (leftFound == NULL && rightFound == NULL){
        addToFreeList(newMem);
    } else {
        merge(leftFound, newMem);
        merge(leftFound, rightFound);
        addToFreeList(leftFound);
    }
        if (SBRK_SIZE != (size + TOTAL_METADATA_SIZE)) {
            newMem = split(newMem, size + TOTAL_METADATA_SIZE);
        }
        setCanary(newMem);
        return (void*) (newMem + 1);
    }
    return NULL;
}

/* REALLOC
 * See PDF for documentation
 */
void *my_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        void* newMem = my_malloc(size);

        return newMem;
     }
    else if (size == 0 && ptr != NULL) {
        my_free(ptr);
        return NULL;
    }
    else {
        metadata_t* canaryMatch = (metadata_t*)ptr-1;
        unsigned long canary = ((uintptr_t)canaryMatch ^ CANARY_MAGIC_NUMBER)+1890;

        if (canaryMatch->canary != canary) {
            my_malloc_errno = CANARY_CORRUPTED;
            return NULL;
        }
        if(*(unsigned long*)((uint8_t*)canaryMatch+canaryMatch->size + sizeof (metadata_t)) != canary) {
            my_malloc_errno = CANARY_CORRUPTED;
            return NULL;
        }
        void* newMem = my_malloc(size);
        if (newMem == NULL) {
            my_malloc_errno = OUT_OF_MEMORY;
            return NULL;
        }
        memcpy(newMem, ptr, size);
        my_malloc_errno = NO_ERROR;
        return newMem;
     }
    // UNUSED_PARAMETER(ptr);
    // UNUSED_PARAMETER(size);
}

/* CALLOC
 * See PDF for documentation
 */
void *my_calloc(size_t nmemb, size_t size) {
    void* memBlock = my_malloc(nmemb*size);
    if (memBlock == NULL) {
        return NULL;
    }
    my_malloc_errno = NO_ERROR;
    metadata_t* memBlockMeta = (metadata_t*)memBlock - 1;
    memBlockMeta->next = NULL;
    memset(memBlock, 0, nmemb * size);
    return memBlock;
}

/* FREE
 * See PDF for documentation
 */
void my_free(void *ptr) {
    my_malloc_errno = NO_ERROR;
    if (ptr == NULL) {
        my_malloc_errno = NO_ERROR;
        return;
    }
    metadata_t* freed = ((metadata_t*)ptr)-1;
    unsigned long canary = ((uintptr_t)freed^CANARY_MAGIC_NUMBER)+1890;
    if (*(unsigned long*)((uint8_t*)freed+freed->size + sizeof(metadata_t))!=canary || freed->canary != canary ) {
        my_malloc_errno = CANARY_CORRUPTED;
        return;
    }
    metadata_t* leftFound = find_left(freed);
    metadata_t* rightFound = find_right(freed);
        if (leftFound != NULL && rightFound == NULL) {
            merge(leftFound, freed);
            addToFreeList(leftFound);
        }
         else if (rightFound != NULL && leftFound == NULL) {
            merge(freed, rightFound);
            addToFreeList(freed);
        }
    else if (leftFound == NULL && rightFound == NULL){
        addToFreeList(freed);
    } else {
        merge(leftFound, freed);
        merge(leftFound, rightFound);
        addToFreeList(leftFound);
    }
    my_malloc_errno = NO_ERROR;
    return;
}

static void addToFreeList(metadata_t* mem) {
    if (size_list == NULL) {
        size_list = mem;
        return;
    }
    if (mem->size < size_list->size) {
        mem->next = size_list;
        size_list = mem;
        return;
    }
    metadata_t *curr = size_list->next;
    metadata_t *prev = size_list;
    while (curr != NULL && curr->size <= mem->size) {
        prev=curr;
        curr=curr->next;
    }
    if (curr == NULL) {
        prev->next = mem;
    } else {
        prev->next = mem;
        mem->next = curr;
    }

}

static void removeFromFreeList(metadata_t* block) {
    if (size_list == NULL) {
        return;
    }
    if (block == size_list) {
        size_list = block->next;
        block -> next = NULL;
    } else {
        metadata_t* curr = size_list;
        metadata_t* prev = NULL;
        while (curr != block) {
            prev = curr;
            curr = curr->next;
            if (curr == NULL) {
                return;
            }
        }
        prev->next = curr->next;
        block->next = NULL;

    }

}

static void setCanary(metadata_t* block) {
    unsigned long canary = ((uintptr_t)block ^ CANARY_MAGIC_NUMBER) + 1890;
    block->canary = canary;
    *(unsigned long*)((uint8_t*)block + block->size + TOTAL_METADATA_SIZE - sizeof(unsigned long)) = canary;
}

static metadata_t* split(metadata_t* block, size_t size) {
    metadata_t* newBlock = (metadata_t*)((uint8_t*)block + block->size + TOTAL_METADATA_SIZE - size);
    newBlock->size = size - TOTAL_METADATA_SIZE;
    removeFromFreeList(block);
    block->size = block->size - size;
    metadata_t* leftFound = find_left(block);
    metadata_t* rightFound = find_right(block);
        if (leftFound != NULL && rightFound == NULL) {
            merge(leftFound, block);
            addToFreeList(leftFound);
        }
         else if (rightFound != NULL && leftFound == NULL) {
            merge(block, rightFound);
            addToFreeList(block);
        }
    else if (leftFound == NULL && rightFound == NULL){
        addToFreeList(block);
    } else {
        merge(leftFound, block);
        merge(leftFound, rightFound);
        addToFreeList(leftFound);
    }
    return newBlock;
}

static metadata_t* find_right(metadata_t* right) {
    metadata_t* curr = size_list;
    metadata_t* endOfBlock = (metadata_t*)((uint8_t*)right + right->size + TOTAL_METADATA_SIZE);
    while (curr != NULL) {
        if (endOfBlock == curr) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

static metadata_t* find_left(metadata_t* left) {
    metadata_t* curr = size_list;
    while (curr != NULL) {
        metadata_t* endOfCurr = (metadata_t*)((uint8_t*)curr + curr->size + TOTAL_METADATA_SIZE);
        if (endOfCurr == left) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;

}

static void merge(metadata_t* left, metadata_t* right) {
    removeFromFreeList(left);
    removeFromFreeList(right);
    left->size += right->size + TOTAL_METADATA_SIZE;
}
