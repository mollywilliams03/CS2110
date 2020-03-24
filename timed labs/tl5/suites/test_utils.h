#include "../tl5.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define tcase_hack(suite, setup_fixture, teardown_fixture, func) { \
    TCase *tc = tcase_create(STRINGIFY(func)); \
    tcase_add_checked_fixture(tc, setup_fixture, teardown_fixture); \
    tcase_add_test(tc, func); \
    suite_add_tcase(s, tc); \
}

typedef struct pokemon poke;

/* Given to you for free, However you better know how to do this come time for
 * the final exam!
 * A function pointer type that points to a function that takes in a struct pokemon * and
 * returns nothing, call it list_op
 */
//typedef void (*list_op)(struct pokemon *);

/* A function pointer type that points to a function that takes in a struct pokemon * and
 * a struct pokemon ** (used to pass back a pointer to the newly allocated data) and returns
 * a boolean indicating success or failure, call it list_copy
 */
//typedef int (*list_copy)(const struct pokemon *, struct pokemon **);

/* A function pointer type that points to a function that takes in two struct pokemon * and
 * returns an int, call it list_eq
 */
//typedef int (*list_eq)(const struct pokemon *, const struct pokemon *);

//extern node *_create_node(struct pokemon *data);
extern struct list *_create_list(void);
//extern struct hash_table *_create_hash_table(void);
extern int _push_front(struct list *listToAddTo, int level, char* type);
extern void _empty_list(struct list *listToEmpty);
extern void _free_list_nodes_and_data(struct list *listToEmpty);
//extern void _free_list_nodes(struct list *listToEmpty);
//extern int _hash_table_add(struct hash_table *hash_table_to_add_to,
//                     struct pokemon *data_to_add);
//extern void _free_hash_table_and_data(struct hash_table *table, list_op free_func);
