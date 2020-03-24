// Homework 10 Tests, Fall 2018
// Structure by Austin, actual work by Jim and Sanjay (RIP)
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

int dog_name_is(Dog *dog, const char* name) {
    return strcmp(dog->name, name) == 0;
}

static void reset_mallocs_until_fail(void) {
    mallocs_until_fail = -1;
}

static struct list *_create_length_1_list(void) {
    struct list *shortList = _create_list();
    _push_front(shortList, dog_new("Marley", "Yellow Lab", 13));
    return shortList;
}

static struct list *_create_longer_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, dog_new("Scooby", "Great Dane", 7));
    _push_front(longerList, dog_new("Marley", "Yellow Lab", 13));
    _push_front(longerList, dog_new("Fido", "Pointer", 16));
    return longerList;
}

static struct list *_create_longer_list2(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, dog_new("Timmy", "Dachshund", 1));
    _push_front(longerList, dog_new("Marley", "Yellow Lab", 4));
    _push_front(longerList, dog_new("Doug", "Pug", 2));
    return longerList;
}

static struct list *_create_even_longer_list(void) {
    struct list *longerList = _create_list();
    _push_front(longerList, dog_new("Timmy", "Dachshund", 1));
    _push_front(longerList, dog_new("Marley", "Yellow Lab", 4));
    _push_front(longerList, dog_new("Doug", "Pug", 5));
    _push_front(longerList, dog_new("Fido", "Golden Retriever", 3));
    _push_front(longerList, dog_new("Scooby", "Great Dane", 8));
    _push_front(longerList, dog_new("Spot", "Dalmation", 2));
    return longerList;
}

void teardown_bar_list(void) {
    if (l != NULL) {
        _free_list_nodes_and_data(l, dog_free);
        l = NULL;
    }
}

/******************************************************************************/
/*************************** create_list() tests ******************************/
/******************************************************************************/
START_TEST(test_list_create_list_basic) {
    struct list *l1 = create_list();
    ck_assert(l1);
    ck_assert(!l1->size);
    ck_assert(!l1->head);
    free(l1);
}
END_TEST

START_TEST(test_list_create_list_malloc_failure) {
    mallocs_until_fail = 0;
    struct list *l1 = create_list();
    ck_assert(!l1);
}
END_TEST

/******************************************************************************/
/************************** push_front() tests ********************************/
/******************************************************************************/
void setup_list_push_front(void) {
    reset_mallocs_until_fail();
    l = _create_list();
    ck_assert(l);
}

void teardown_list_push_front(void) {
    if (l) {
        free(l);
        l = NULL;
    }
}

START_TEST(test_list_push_front_NULL_list) {
    struct dog *b = dog_new("Marley", "Yellow Lab", 13);
    ck_assert(!push_front(NULL, b));
    dog_free(b);
}
END_TEST

START_TEST(test_list_push_front_NULL_data) {
    ck_assert(push_front(l, NULL));
    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(!l->head->next);
    ck_assert(!l->head->data);

    free(l->head);
}
END_TEST

START_TEST(test_list_push_front_empty) {
    struct dog *b = dog_new("Henry", "Golden Retriever", 21);
    ck_assert(push_front(l, b));
    ck_assert_int_eq(l->size, 1);
    ck_assert(l->head);
    ck_assert(!l->head->next);
    ck_assert_ptr_eq(l->head->data, b);

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head);
    dog_free(b);
}
END_TEST

START_TEST(test_list_push_front_nonempty) {
    // Put some stuff in the struct list
    struct dog *b0 = dog_new("Yeezy", "Work", 1);
    struct dog *b1 = dog_new("Yeezy", "it", 2);
    struct dog *b2 = dog_new("Yeezy", "out", 3);
    l->head = _create_node(b0);
    l->head->next = _create_node(b1);
    l->size = 3;

    struct dog *b3 = dog_new("Yeezy", "No dessert", 4);
    ck_assert(push_front(l, b3));
    ck_assert_int_eq(l->size, 4);
    ck_assert(l->head);
    ck_assert_ptr_eq(l->head->data, b3);

    // Don't use empty_list() because we don't want to nail everyone for
    // memory leaks if it's broken
    free(l->head->next->next->next);
    free(l->head->next->next);
    free(l->head->next);
    free(l->head);
    dog_free(b0);
    dog_free(b1);
    dog_free(b2);
    dog_free(b3);
}
END_TEST

/******************************************************************************/
/************************** push_back() tests *********************************/
/******************************************************************************/
START_TEST(test_list_push_back_empty) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("Gucci", "gucci, can I be your main squeeze", 60);
    ck_assert(push_back(l1, b0));
    ck_assert_ptr_eq(l1->head->data, b0);
    ck_assert_int_eq(l1->size, 1);
    free(l1->head);
    free(l1);
    dog_free(b0);

}
END_TEST
START_TEST(test_list_push_back_non_empty) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("takeoff", "they think i'm dumb, they don't think I see the plot", 10);
    struct dog *b1 = dog_new("chris brown", "hundred on my wrist, jumpin out the rari", 10);

    _push_front(l1, b0);

    ck_assert(push_back(l1, b1));
    ck_assert_ptr_eq(b0, l1->head->data);
    ck_assert_int_eq(l1->size, 2);

    free(l1->head->next);
    free(l1->head);
    dog_free(b0);
    dog_free(b1);
    free(l1);
}
END_TEST
START_TEST(test_list_push_back_null) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("kodak black", "snatch your baby girl", 10);
    ck_assert(!push_back(NULL, b0));
    ck_assert(push_back(l1, NULL));
    ck_assert_int_eq(l1->size, 1);
    ck_assert(!l1->head->data);

    dog_free(b0);
    free(l1->head);
    free(l1);
}
END_TEST


/******************************************************************************/
/************************** add_at_index() tests ***************************************/
/******************************************************************************/
START_TEST(test_list_add_at_index_out_of_bounds) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("young thug", "learn how to dress from me", 10);

    ck_assert(!add_at_index(l1, b0, -1));

    _push_front(l1, b0);

    ck_assert(!add_at_index(l1, b0, 2));

    free(l1->head);
    free(l1);
    dog_free(b0);

}
END_TEST

START_TEST(test_list_add_at_index_empty_list) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("bobby shmurda", "shooting is my hobby", 1);
    struct dog *b1 = dog_new("Ayo", "I just want a rollie rollie rollie and a dab of ranch", 1);

    ck_assert(add_at_index(l1, b0, 0));
    ck_assert_int_eq(l1->size, 1);
    ck_assert_ptr_eq(l1->head->data, b0);

    ck_assert(!add_at_index(l1, b1, 2));

    ck_assert(add_at_index(l1, b1, 1));

    ck_assert_int_eq(l1->size, 2);

    _free_list_nodes_and_data(l1, dog_free);


}
END_TEST

START_TEST(test_list_add_at_index_non_empty_list) {

    struct list *l1 = _create_longer_list();
    struct dog *b0 = dog_new("gucci", "flying in my rari like a bat that just flew out of hell", 1);
    ck_assert(add_at_index(l1, b0, 1));
    ck_assert_ptr_eq(l1->head->next->data, b0);
    ck_assert_int_eq(l1->size, 4);

    _free_list_nodes_and_data(l1, dog_free);

}
END_TEST

START_TEST(test_list_add_at_index_null) {
    struct list *l1 = _create_list();
    struct dog *b0 = dog_new("gucci", "I'm from the east of A T L but ballin in the Cali hills", 1);

    ck_assert(!add_at_index(NULL, NULL, 0));

    ck_assert(!add_at_index(NULL, b0, 0));

    ck_assert(add_at_index(l1, NULL, 0));
    ck_assert_int_eq(l1->size, 1);
    ck_assert(!l1->head->data);

    free(l1->head);
    free(l1);
    dog_free(b0);
}
END_TEST
/******************************************************************************/
/*************************** pop_front() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_front_NULL_list) {
    struct dog *dataOut = (struct dog *) 0xDEADBEEFU;
    ck_assert(!pop_front(NULL, &dataOut));
}
END_TEST

START_TEST(test_list_pop_front_NULL_dataOut) {
    l = _create_list();
    ck_assert(!pop_front(l, NULL));
}
END_TEST

START_TEST(test_list_pop_front_empty) {
    l = _create_list();
    struct dog *dataOut = (struct dog *) 0xDEADBEEFU;
    ck_assert(!pop_front(l, &dataOut));
}
END_TEST

START_TEST(test_list_pop_front_nonempty) {
    l = _create_length_1_list();
    struct dog *marley = NULL;
    int result = pop_front(l, &marley);
    ck_assert(marley);
    int nameCheck = dog_name_is(marley, "Marley");
    dog_free(marley);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_front_longer_list) {
    l = _create_longer_list();
    struct dog *data = NULL;
    int result = pop_front(l, &data);
    ck_assert(data);
    int nameCheck = dog_name_is(data, "Fido");
    dog_free(data);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(dog_name_is(l->head->data, "Marley"));
    ck_assert(dog_name_is(l->head->next->data, "Scooby"));
    ck_assert(!l->head->next->next);

    result = pop_front(l, &data);
    nameCheck = dog_name_is(data, "Marley");
    dog_free(data);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 1);
    ck_assert(dog_name_is(l->head->data, "Scooby"));
    ck_assert(!l->head->next);
}
END_TEST

/******************************************************************************/
/**************************** pop_back() tests ********************************/
/******************************************************************************/
START_TEST(test_list_pop_back_NULL_list) {
    struct dog *dataOut = (struct dog *)0xDEADBEEFU;
    ck_assert(!pop_back(NULL, &dataOut));
}
END_TEST

START_TEST(test_list_pop_back_NULL_dataOut) {
    l = _create_list();
    ck_assert(!pop_back(l, NULL));
}
END_TEST

START_TEST(test_list_pop_back_empty) {
    l = _create_list();
    struct dog *dataOut = (struct dog *)0xDEADBEEFU;
    ck_assert(!pop_back(l, &dataOut));
}
END_TEST

START_TEST(test_list_pop_back_nonempty) {
    l = _create_length_1_list();
    struct dog *marley = NULL;
    int result = pop_back(l, (struct dog **) &marley);
    ck_assert(marley);

    int nameCheck = dog_name_is(marley, "Marley");
    dog_free(marley);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_pop_back_longer_list) {
    l = _create_longer_list();
    struct dog *data = NULL;
    int result = pop_back(l, (struct dog **) &data);
    ck_assert(data);
    int name_check = dog_name_is(data, "Scooby");
    dog_free(data);
    ck_assert(result);
    ck_assert(name_check);
    ck_assert_int_eq(l->size, 2);
    ck_assert(dog_name_is(l->head->data, "Fido"));
    ck_assert(dog_name_is(l->head->next->data, "Marley"));
    ck_assert(!l->head->next->next);

    result = pop_back(l, (struct dog **) &data);
    name_check = dog_name_is(data, "Marley");
    dog_free(data);
    ck_assert(result);
    ck_assert(name_check);
    ck_assert_int_eq(l->size, 1);
    ck_assert(dog_name_is(l->head->data, "Fido"));
    ck_assert(!l->head->next);
}
END_TEST

/******************************************************************************/
/**************************** remove_at_index() tests *****************************/
/******************************************************************************/
START_TEST(test_list_remove_at_index_NULL_list) {
    struct dog *dataOut = (struct dog *) 0xDEADBEEFU;
    ck_assert(!remove_at_index(NULL, &dataOut, 0));
}
END_TEST

START_TEST(test_list_remove_at_index_NULL_dataOut) {
    l = _create_length_1_list();
    ck_assert(!remove_at_index(l, NULL, 0));
}
END_TEST

START_TEST(test_list_remove_at_index_out_of_bounds) {
    l = _create_length_1_list();
    ck_assert(!remove_at_index(l, NULL, -1));
}
END_TEST

START_TEST(test_list_remove_at_index_front) {
    l = _create_longer_list();
    struct dog *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert(dataOut);
    int nameCheck = dog_name_is(dataOut, "Fido");
    dog_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(dog_name_is(l->head->data, "Marley"));
    ck_assert(dog_name_is(l->head->next->data, "Scooby"));
}
END_TEST

START_TEST(test_list_remove_at_index_middle) {
    l = _create_longer_list();
    struct dog *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 1);
    ck_assert(dataOut);
    int nameCheck = dog_name_is(dataOut, "Marley");
    dog_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(dog_name_is(l->head->data, "Fido"));
    ck_assert(dog_name_is(l->head->next->data, "Scooby"));
    ck_assert(!l->head->next->next);
}
END_TEST

START_TEST(test_list_remove_at_index_back) {
    l = _create_longer_list();
    struct dog *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 2);
    ck_assert(dataOut);
    int nameCheck = dog_name_is(dataOut, "Scooby");
    dog_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 2);
    ck_assert(dog_name_is(l->head->data, "Fido"));
    ck_assert(dog_name_is(l->head->next->data, "Marley"));
    ck_assert(!l->head->next->next);
}
END_TEST

START_TEST(test_list_remove_at_index_length_1) {
    l = _create_length_1_list();
    struct dog *dataOut = NULL;
    int result = remove_at_index(l, &dataOut, 0);
    ck_assert(dataOut);
    int nameCheck = dog_name_is(dataOut, "Marley");
    dog_free(dataOut);
    ck_assert(result);
    ck_assert(nameCheck);
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);
}
END_TEST

/******************************************************************************/
/************************** empty_list() tests ********************************/
/******************************************************************************/
START_TEST(test_list_empty_list_NULL_list) {
    // Success if there is no error
    empty_list(NULL);
}
END_TEST

START_TEST(test_list_empty_list_empty) {
    l = _create_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_length_1) {
    l = _create_length_1_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

START_TEST(test_list_empty_list_longer_list) {
    l = _create_longer_list();
    empty_list(l);
    ck_assert_int_eq(l->size, 0);
}
END_TEST

/******************************************************************************/
/******************************* get() tests **********************************/
/******************************************************************************/
void checkLongerListUnchanged(void) {
    ck_assert(dog_name_is(l->head->data, "Fido"));
    ck_assert(dog_name_is(l->head->next->data, "Marley"));
    ck_assert(dog_name_is(l->head->next->next->data, "Scooby"));
    ck_assert(!l->head->next->next->next);
}

START_TEST(test_list_get_NULL_list) {
    struct dog *b = (struct dog *)0xDEADBEEFU;
    ck_assert(!get(NULL, 0, &b));
}
END_TEST

START_TEST(test_list_get_NULL_dataOut) {
    l = _create_longer_list();
    ck_assert(!get(l, 0, NULL));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_negative_index) {
    l = _create_longer_list();
    struct dog *b = (struct dog *) 0xDEADBEEFU;
    ck_assert(!get(l, -1, &b));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_front) {
    l = _create_longer_list();
    struct dog *b = (struct dog *) 0xDEADBEEFU;
    ck_assert(get(l, 0, &b));
    ck_assert(dog_name_is(b, "Fido"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_middle) {
    l = _create_longer_list();
    struct dog *b = (struct dog *) 0xDEADBEEFU;
    ck_assert(get(l, 1, &b));
    ck_assert(dog_name_is(b, "Marley"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_back) {
    l = _create_longer_list();
    struct dog *b = (struct dog *)0xDEADBEEFU;
    ck_assert(get(l, 2, &b));
    ck_assert(dog_name_is(b, "Scooby"));
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_get_out_of_bounds_index) {
    l = _create_longer_list();
    struct dog *b = (struct dog *) 0xDEADBEEFU;
    ck_assert(!get(l, 3, &b));
    checkLongerListUnchanged();
}
END_TEST

/******************************************************************************/
/**************************** contains() tests ********************************/
/******************************************************************************/

START_TEST(test_list_contains_NULL_list) {
    struct dog *henry = dog_new("Henry", "Golden Retriever", 21);
    struct dog *dataOut = (struct dog *) 0xDEADBEEFU;
    int result = contains(NULL, (struct dog *) henry, &dataOut);
    dog_free(henry);
    ck_assert(!result);
}
END_TEST

START_TEST(test_list_contains_NULL_dataOut) {
    struct dog *henry = dog_new("Henry", "Golden Retriever", 21);
    l = _create_longer_list();
    int result = contains(l, (struct dog *) henry, NULL);
    dog_free(henry);
    ck_assert(!result);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_empty) {
    l = _create_list();
    struct dog *henry = dog_new("Henry", "Golden Retriever", 21);
    struct dog *dataOut = (struct dog *) 0xDEADBEEFU;
    int result = contains(l, (struct dog *) henry, &dataOut);
    dog_free(henry);
    ck_assert(!result);
    ck_assert(!dataOut);
}
END_TEST

START_TEST(test_list_contains_not_contained) {
    l = _create_longer_list();
    struct dog *henry = dog_new("Marlet", "Yellow Lab", 13);
    struct dog *dataOut = (struct dog *)0xDEADBEEFU;
    int result = contains(l, (struct dog *) henry, &dataOut);
    dog_free(henry);
    ck_assert(!result);
    ck_assert(!dataOut);
    checkLongerListUnchanged();
}
END_TEST

START_TEST(test_list_contains_is_contained) {
    l = _create_longer_list();
    struct dog *marley = dog_new("Marley", "Yellow Lab", 13);
    struct dog *dataOut = (struct dog *)0xDEADBEEFU;
    int result = contains(l, (struct dog *) marley, &dataOut);
    dog_free(marley);
    ck_assert(result);
    ck_assert(dataOut != marley);
    ck_assert(dog_name_is(dataOut, "Marley"));
    checkLongerListUnchanged();
}
END_TEST

/*************************** zip() tests **************************************/
/******************************************************************************/

START_TEST(test_zip_nonempty_lists) {
    struct list *l1 = _create_longer_list2();
    struct list *l2 = _create_longer_list2();
    l2->head->data->name[3] = 0;
    l2->head->next->data->name[3] = 0;
    l2->head->next->next->data->name[3] = 0;
    zip(l1, l2);
    ck_assert(l1);
    ck_assert_int_eq(l1->size, 6);
    ck_assert(dog_name_is(l1->head->data, "Doug"));
    ck_assert(dog_name_is(l1->head->next->data, "Dou"));
    ck_assert(dog_name_is(l1->head->next->next->data, "Marley"));
    ck_assert(dog_name_is(l1->head->next->next->next->data, "Mar"));
    ck_assert(dog_name_is(l1->head->next->next->next->next->data, "Timmy"));
    ck_assert(dog_name_is(l1->head->next->next->next->next->next->data, "Tim"));
    ck_assert(!l2->head);
    ck_assert_int_eq(l2->size, 0);
    _free_list_nodes_and_data(l1, dog_free);
    _free_list_nodes_and_data(l2, dog_free);
}
END_TEST

START_TEST(test_zip_first_list_empty) {
    struct list *l1 = _create_list();
    struct list *l2 = _create_longer_list2();
    zip(l1, l2);
    ck_assert(l1);
    ck_assert_int_eq(l1->size, 3);
    ck_assert(dog_name_is(l1->head->data, "Doug"));
    ck_assert(dog_name_is(l1->head->next->data, "Marley"));
    ck_assert(dog_name_is(l1->head->next->next->data, "Timmy"));
    ck_assert(!l2->head);
    ck_assert_int_eq(l2->size, 0);
    _free_list_nodes_and_data(l1, dog_free);
    _free_list_nodes_and_data(l2, dog_free);
}
END_TEST

START_TEST(test_zip_second_list_empty) {
    struct list *l1 = _create_longer_list2();
    struct list *l2 = _create_list();
    zip(l1, l2);
    ck_assert(l1);
    ck_assert_int_eq(l1->size, 3);
    ck_assert(dog_name_is(l1->head->data, "Doug"));
    ck_assert(dog_name_is(l1->head->next->data, "Marley"));
    ck_assert(dog_name_is(l1->head->next->next->data, "Timmy"));
    ck_assert(!l2->head);
    ck_assert_int_eq(l2->size, 0);
    _free_list_nodes_and_data(l1, dog_free);
    _free_list_nodes_and_data(l2, dog_free);
}
END_TEST

START_TEST(test_zip_null_list) {
    struct list *l1 = NULL;
    struct list *l2 = _create_longer_list2();
    zip(l1, l2);
    ck_assert(l2);
    ck_assert_int_eq(l2->size, 3);
    ck_assert(dog_name_is(l2->head->data, "Doug"));
    ck_assert(dog_name_is(l2->head->next->data, "Marley"));
    ck_assert(dog_name_is(l2->head->next->next->data, "Timmy"));
    ck_assert(!l1);
    _free_list_nodes_and_data(l2, dog_free);
}
END_TEST


/******************************************************************************/
/*************************** sort() tests *************************************/
/******************************************************************************/

START_TEST(test_sort_basic_list) {
    l = _create_longer_list2();
    sort(l);
    ck_assert(l);
    ck_assert_int_eq(l->size, 3);
    ck_assert(dog_name_is(l->head->data, "Timmy"));
    ck_assert(dog_name_is(l->head->next->data, "Doug"));
    ck_assert(dog_name_is(l->head->next->next->data, "Marley"));
}
END_TEST

START_TEST(test_sort_longer_list) {
    l = _create_even_longer_list();
    sort(l);
    ck_assert(l);
    ck_assert_int_eq(l->size, 6);
    ck_assert(dog_name_is(l->head->data, "Timmy"));
    ck_assert(dog_name_is(l->head->next->data, "Spot"));
    ck_assert(dog_name_is(l->head->next->next->data, "Fido"));
    ck_assert(dog_name_is(l->head->next->next->next->data, "Marley"));
    ck_assert(dog_name_is(l->head->next->next->next->next->data, "Doug"));
    ck_assert(dog_name_is(l->head->next->next->next->next->next->data, "Scooby"));
}
END_TEST


START_TEST(test_sort_short_list) {
    l = _create_length_1_list();
    sort(l);
    ck_assert(l);
    ck_assert_int_eq(l->size, 1);
    ck_assert(dog_name_is(l->head->data, "Marley"));
}
END_TEST

START_TEST(test_sort_empty_list) {
    l = _create_list();
    sort(l);
    ck_assert(l);
    ck_assert_int_eq(l->size, 0);
    ck_assert(!l->head);
}
END_TEST

Suite *list_suite(void) {
    Suite *s = suite_create("struct list");

    // create_list() tests
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_basic);
    tcase_hack(s, reset_mallocs_until_fail, NULL, test_list_create_list_malloc_failure);

    // push_front() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_NULL_data);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_front_nonempty);

    // push_back()tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_non_empty);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_push_back_null);

    // add_at_index() tests
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_out_of_bounds);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_non_empty_list);
    tcase_hack(s, setup_list_push_front, teardown_list_push_front, test_list_add_at_index_null);

    // pop_front() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_front_longer_list);

    // pop_back() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_nonempty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_pop_back_longer_list);

    // remove_at_index() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_out_of_bounds);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_remove_at_index_length_1);

    // empty_list() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_length_1);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_empty_list_longer_list);

    // get() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_negative_index);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_front);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_middle);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_back);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_get_out_of_bounds_index);

    // contains() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_NULL_dataOut);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_not_contained);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_list_contains_is_contained);

    // zip() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_zip_nonempty_lists);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_zip_first_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_zip_second_list_empty);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_zip_null_list);
    
    // sort() tests
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_sort_basic_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_sort_longer_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_sort_short_list);
    tcase_hack(s, reset_mallocs_until_fail, teardown_bar_list, test_sort_empty_list);


    return s;
}
