#include "todo.h"

/**
 * Just like fgets except it omits the newline at the end if there is one! Check out the man page for fgets!
 */
char *fgets_no_newline(char *buffer, int buf_length, FILE *stream) {
    char *result = fgets(buffer, buf_length, stream);
    if (result == NULL) {
        return 0;
    }
    int line_length = strlen(buffer);
    if (line_length > 0 && buffer[line_length - 1] == '\n') {
        buffer[line_length - 1] = '\0';
    }
    return result;
}

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
int read_todo_list_item(FILE *stream) {
    if (Todo_list_length >= TODO_LIST_MAX) {
        return 0;
    }
    if (fgets_no_newline(Todo_list[Todo_list_length].title, TITLE_LENGTH_MAX, stream) == NULL) {
        return 0;
    }
    if (fgets_no_newline(Todo_list[Todo_list_length].description, DESCRIPTION_LENGTH_MAX, stream) == NULL) {
        return 0;
    }
    char num_buffer[10];
    if (fgets(num_buffer, 10, stream) == NULL) {
        return 0;
    }
    Todo_list[Todo_list_length].is_done = atoi(num_buffer);
    if (fgets(num_buffer, 10, stream) == NULL) {
        return 0;
    }
    Todo_list[Todo_list_length].due_day = atoi(num_buffer);
    if (fgets(num_buffer, 10, stream) == NULL) {
        return 0;
    }
    Todo_list[Todo_list_length].due_month = atoi(num_buffer);
    if (fgets(num_buffer, 10, stream) == NULL) {
        return 0;
    }
    Todo_list[Todo_list_length].due_year = atoi(num_buffer);
    Todo_list_length++;
    return 1;
}
