// Timed Lab 5 Tests, Spring 2019
// Structure by Austin, actual work by Jim and Sanjay (RIP), lots of change by Maddie (why do I do this)
//
// Warning: much the structure of this file is shamelessly copypasted from
// https://libcheck.github.io/check/doc/check_html/check_3.html

#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "test_utils.h"

static struct list *l;

// The number of mallocs in user code until the next one fails, or -1 for
// successful mallocs
int mallocs_until_fail = -1;

/* MADDIE TODO*/
//int poke_type_is(st *dog, const char* name) {
//    return strcmp(dog->name, name) == 0;
//}

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct list *_create_list_empty(void) {
    struct list* emptyList = _create_list();
    return emptyList;
}

static struct list *_create_length_1_list(void) {
    struct list *shortList = _create_list();
    _push_front(shortList, 5, "pichu");
    return shortList;
}

static struct list *_create_longer_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, 5, "pichu");
    _push_front(longerList, 7, "pikachu");
    _push_front(longerList, 9, "raichu");
    return longerList;
}

//static struct list *_create_longer_list2(void) {
//    struct list *longerList = _create_list();
//    _push_front(longerList, 3, "squirtle");
//    _push_front(longerList, 5, "wartortle");
//    _push_front(longerList, 7, "blastoise");
//    return longerList;
//}

//static struct list *_create_even_longer_list(void) {
//    struct list *longerList = _create_list();
//    _push_front(longerList, 1, "eevee");
//    _push_front(longerList, 2, "jolteon");
//    _push_front(longerList, 4, "flareon");
//    _push_front(longerList, 6, "umbreon");
//    _push_front(longerList, 8, "leafeon");
//    _push_front(longerList, 10, "sylveon");
//    _push_front(longerList, 12, "vaporeon");
//    return longerList;
//}

void teardown_bar_list(void) {
    if (l != NULL) {
        _free_list_nodes_and_data(l);
        l = NULL;
    }
}

/******************************************************************************/
/*************************** copy_list() tests ***************************/
/******************************************************************************/
START_TEST(test_list_copy_basic_easy) {
    struct list *l1 = _create_length_1_list();
    struct list *l2 = copy_list(l1);
    
    ck_assert(l2);
    
    poke *current_l1 = l1->starter_pokemon;
    poke *current_l2 = l2->starter_pokemon;
    
    //checks to make sure l2 isn't null
    ck_assert(current_l2);
    
    //checks to ensure it is the correct type and the correct level
    ck_assert_str_eq(current_l1 -> type, current_l2 -> type);
    ck_assert_int_eq(current_l1 -> level, current_l2 -> level);
    
    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_copy_basic_hard) {
    struct list *l1 = _create_length_1_list();
    struct list *l2 = copy_list(l1);
    
    ck_assert(l2);
    
    poke *current_l1 = l1->starter_pokemon;
    poke *current_l2 = l2->starter_pokemon;
    
    //checks to make sure l2 isn't null
    ck_assert(current_l2);
    
    //checks to ensure it is the correct type and the correct level
    ck_assert_str_eq(current_l1 -> type, current_l2 -> type);
    ck_assert_int_eq(current_l1 -> level, current_l2 -> level);
    
    //checks to ensure that they did deep copy - double check this though
    ck_assert_ptr_ne(current_l1, current_l2);
    ck_assert_ptr_ne(current_l1 -> type, current_l2 -> type);
    
    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);
}
END_TEST

START_TEST(test_list_copy_long_easy) {
    struct list *l1 = _create_longer_list();

    struct list *l2 = copy_list(l1);

    ck_assert(l2);

    poke *current_l1 = l1->starter_pokemon;
    poke *current_l2 = l2->starter_pokemon;

    ck_assert(current_l2);

    while (current_l1) {
        ck_assert_str_eq(current_l1 -> type, current_l2 -> type);
        ck_assert_int_eq(current_l1 -> level, current_l2 -> level);
        current_l1 = current_l1->evolve;
        current_l2 = current_l2->evolve;
    }

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);

}
END_TEST

START_TEST(test_list_copy_long_hard) {
    struct list *l1 = _create_longer_list();

    struct list *l2 = copy_list(l1);

    ck_assert(l2);

    poke *current_l1 = l1->starter_pokemon;
    poke *current_l2 = l2->starter_pokemon;

    ck_assert(current_l2);

    while (current_l1) {
        ck_assert_str_eq(current_l1 -> type, current_l2 -> type);
        ck_assert_int_eq(current_l1 -> level, current_l2 -> level);
        ck_assert_ptr_ne(current_l1, current_l2);
        ck_assert_ptr_ne(current_l1 -> type, current_l2 -> type);
        current_l1 = current_l1->evolve;
        current_l2 = current_l2->evolve;
    }

    _free_list_nodes_and_data(l1);
    _free_list_nodes_and_data(l2);

}
END_TEST

START_TEST(test_list_copy_malloc_failure) {
    struct list *l1 = _create_longer_list();

    mallocs_until_fail = 1;
    struct list *l2 = copy_list(l1);

    ck_assert(!l2);

    _free_list_nodes_and_data(l1);
}
END_TEST

START_TEST(test_list_copy_malloc_failure_hard) {
    struct list *l1 = _create_longer_list();

    mallocs_until_fail = 2;
    struct list *l2 = copy_list(l1);

    ck_assert(!l2);

    _free_list_nodes_and_data(l1);
}
END_TEST

START_TEST(test_list_copy_empty_list) {
    struct list *l1 = _create_list_empty();
    struct list *l2 = copy_list(l1);

    ck_assert(l2);
    ck_assert(!l2 -> starter_pokemon);
    free(l1);
    free(l2);
}
END_TEST

START_TEST(test_list_copy_null_list) {
    struct list *l1 = copy_list(NULL);
    ck_assert(!l1);
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/
START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    destroy(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    struct list *l = _create_list();
    destroy(l);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    struct list *l = _create_length_1_list();
    destroy(l);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    struct list *l = _create_longer_list();
    destroy(l);
}
END_TEST

Suite *list_suite(void) {
    Suite *s = suite_create("struct list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_basic_easy);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_basic_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_long_easy);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_long_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_malloc_failure);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_malloc_failure_hard);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_null_list);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_copy_empty_list);
    
    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_longer_list);


    return s;
}
