#ifndef BAR_H
#define BAR_H

extern int copies_until_malloc_fail;
extern int bars_visited;

typedef struct dog {
    char *name;
    char *breed;
    int age;
} Dog;

Dog *dog_new(char *name, char *breed, int age);
void dog_free(Dog *p);
int dog_copy(const Dog *p, Dog **ret);
int dog_eq(const Dog *a, const Dog *b);
int dog_compare(const Dog *a, const Dog *b);
int dog_eq_name(const Dog *a, const Dog *b);
int dog_hash(const Dog *a);

#endif
