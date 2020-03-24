#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TODO_LIST_MAX 100
#define TITLE_LENGTH_MAX 64
#define DESCRIPTION_LENGTH_MAX 128

// Struct for our to-do list items
struct todo_list_item_t {
    char title[TITLE_LENGTH_MAX]; // The title of the item
    char description[DESCRIPTION_LENGTH_MAX]; // The description of the item
    int is_done; // Whether or not the item has been completed... 1 if completed and 0 if not
    int due_day; // The day it is due
    int due_month; // The month it is due
    int due_year; // The year it is due
};

// The global array that will hold our to-do list items
extern struct todo_list_item_t Todo_list[TODO_LIST_MAX];

// The number of items currently in the todo list
extern int Todo_list_length;

/**
 * Just like fgets except it omits the newline at the end if there is one! Check out the man page for fgets!
 */
char *fgets_no_newline(char *buffer, int buf_length, FILE *stream);

/**
 * Reads a todo_list item from a file and appends it to the Todo_list for you!. Assumes that the todo_list item will
 * have its fields separated by newlines in the order:
 *
 * title
 * description
 * is_done (0 or 1)
 * due_day
 * due_month
 * due_year
 *
 * @param stream The file stream to read from.
 * @return 0 If an error occurred or if we reached the end of the file.
 */
int read_todo_list_item(FILE *stream);
