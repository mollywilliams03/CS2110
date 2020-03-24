#include <check.h>
#include <stdlib.h>
#include "dog.h"

int copies_until_malloc_fail = -1;
int bars_visited = 0;

/**
 * Hashes a dog based on the first letter in their name. Names that start
 * with upper case letters hash to negative numbers, and those with lower case
 * letters will hash to 0 - 26.
 */
int dog_hash(const Dog *a) {
    Dog *dog_a = (Dog *)a;
    return (dog_a->name)[0] - 97;
}

/**
 * Allocates a new dog struct on the heap with the given name and word.
 */
Dog * dog_new(char *name, char *breed, int age) {
    Dog *result = malloc(sizeof (Dog));
    ck_assert(result);

    result->name = malloc(strlen(name) + 1);
    ck_assert(result->name);
    strcpy(result->name, name);

    result->breed = malloc(strlen(breed) + 1);
    ck_assert(result->breed);
    strcpy(result->breed, breed);

    result->age = age;

    return result;
}

/**
 * Deallocates the memory for a dog struct.
 */
void dog_free(Dog *p) {
    // At the moment, I don't add NULL pointers
    ck_assert(p);

    Dog *b = (Dog *) p;
    free(b->name);
    free(b->breed);
    free(b);

    bars_visited++;
}

// Used in test_dll_null_data.
// This is separate from dog_free() because I want to catch stray NULL data
// pointers outside test_dll_null_data
void dog_free_null(Dog *p) {
    ck_assert(!p);

    bars_visited++;
}

/**
 * Copies the data for a dog struct to newly allocated heap memory.
 */
int dog_copy(const Dog *p, Dog **ret) {
    if (ret == NULL){
        return 0;
    }

    struct dog *b = (struct dog *) p;
    *ret = dog_new(b->name, b->breed, b->age);
    return 1;
}

// Used in test_dll_null_data.
// This is separate from dog_copy() because I want to catch stray NULL data
// pointers outside test_dll_null_data
Dog *dog_copy_null(const Dog *p) {
    ck_assert(!p);

    bars_visited++;

    return NULL;
}

// Used in test_dll_malloc_fail.
// To prevent valgrind from reporting leaks in copy_dllist() allowed by the
// TAs, return the pointer passed in.
Dog *dog_copy_fake(const Dog *p) {
    if (!copies_until_malloc_fail) {
        // Simulate a failed malloc in copy_func()
        return NULL;
    } else {
        if (copies_until_malloc_fail != -1) {
            copies_until_malloc_fail--;
        }

        // TODO: This cast is a hack, but it shouldn't cause any issues because
        //       we never write to it. It's just a non-NULL value to send back
        return (struct dog *) p;
    }
}

void dog_visit(Dog *p) {
    // At the moment, I don't add NULL pointers
    ck_assert(p);
    bars_visited++;
}

// Used in test_dll_null_data.
// This is separate from dog_visit() because I want to catch stray NULL data
// pointers outside test_dll_null_data
void dog_visit_null(Dog *p) {
    ck_assert(!p);
    bars_visited++;
}

int dog_eq(const struct dog *a, const Dog *b) {
    ck_assert(a);
    ck_assert(b);
    struct dog *dog_a = (struct dog *) a;
    struct dog *dog_b = (struct dog *) b;
    return strcmp(dog_a->name, dog_b->name) || strcmp(dog_a->breed, dog_b->breed) || dog_a->age != dog_b->age;
}

/**
 * Returns the string comparison of the two dog structs' names. Check out
 * the man page for strcmp! (Fun fact, if you're on vim you can put your cursor
 * over the word strcmp (or any c standard library function) and press
 * shift+k to automatically open the man page)
 */
int dog_eq_name(const Dog *a, const Dog *b) {
    ck_assert(a);
    ck_assert(b);
    struct dog *dog_a = (struct dog *) a;
    struct dog *dog_b = (struct dog *) b;

    bars_visited++;

    return strcmp(dog_a->name, dog_b->name);
}

/**
 * Returns the string comparison of the two dog structs' names. Check out
 * the man page for strcmp! (Fun fact, if you're on vim you can put your cursor
 * over the word strcmp (or any c standard library function) and press
 * shift+k to automatically open the man page)
 */
int dog_compare(const Dog *a, const Dog *b) {
    ck_assert(a);
    ck_assert(b);

    return a->age - b->age;
}

// Used in test_dll_null_data.
// This is separate from dog_eq() because I want to catch stray NULL data
// pointers outside test_dll_null_data
// Always find the first match
int dog_eq_null_match(const Dog *a, const Dog *b) {
    ck_assert(!a);
    ck_assert(!b);

    bars_visited++;

    return 0;
}

// Same, but never finds a match
int dog_eq_null_no_match(const Dog *a, const Dog *b) {
    ck_assert(!a);
    ck_assert(!b);

    bars_visited++;

    return 1;
}
