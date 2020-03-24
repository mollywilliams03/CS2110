#include "todo.h"
#include "useful_strings.h"
#include <stdio.h>
//#include "todo_data.c"



void optionOne (void) {
    printf(TODO_LIST_HEADER);
    for (int i = 0; i < Todo_list_length; i++) {
        printf("%s\n", Todo_list[i].title);
        printf("\n");
        if (Todo_list[i].is_done == 1) {
            printf(COMPLETED);
        } else {
            if (Todo_list[i].due_month <= 9) {
                printf("Due: 0%d/", Todo_list[i].due_month);
            } else {
                printf("Due: %d/", Todo_list[i].due_month);
            }
            if (Todo_list[i].due_day <= 9) {
                printf("0%d/", Todo_list[i].due_day);
            } else {
                printf("%d/", Todo_list[i].due_day);
            }
            if (Todo_list[i].due_year < 1000) {
                printf("0%d\n", Todo_list[i].due_year);
            } else {
                printf("%d\n", Todo_list[i].due_year);
            }
        }
        printf("Description: %s\n", Todo_list[i].description);
        printf(LINE_BREAK);
    }

}

void optionTwo (void) {
    printf(ADD_TO_LIST_HEADER);
    if (Todo_list_length >= TODO_LIST_MAX) {
        printf(LIST_MAX);
        return;
    }
    printf(ADD_TO_LIST);
    if (fgets_no_newline(Todo_list[Todo_list_length].title, TITLE_LENGTH_MAX, stdin) == NULL) {
        return;
    }
    if (fgets_no_newline(Todo_list[Todo_list_length].description, DESCRIPTION_LENGTH_MAX, stdin) == NULL) {
        return;
    }
    char num_buffer[10];
    if (fgets(num_buffer, 10, stdin) == NULL) {
        return;
    }
    Todo_list[Todo_list_length].is_done = atoi(num_buffer);
    if (fgets(num_buffer, 10, stdin) == NULL) {
        return;
    }
    Todo_list[Todo_list_length].due_day = atoi(num_buffer);
    if (fgets(num_buffer, 10, stdin) == NULL) {
        return;
    }
    Todo_list[Todo_list_length].due_month = atoi(num_buffer);
    if (fgets(num_buffer, 10, stdin) == NULL) {
        return;
    }
    Todo_list[Todo_list_length].due_year = atoi(num_buffer);
    Todo_list_length++;
    return;

}


void optionThree(void) {
    printf(MARK_ITEM_COMPLETED_HEADER);
    printf(MARK_ITEM_USER_INPUT);
    printf(GRAB_INPUT);
    char buffer1[128];
    if (fgets(buffer1, 128, stdin) == NULL) {
        return;
    }
    int isComplete = atoi(buffer1);
    Todo_list[isComplete].is_done = 1;
}

void optionFour(void) {
    printf(REMOVE_ITEM_HEADER);
    int count = 0;
    int spot = 0;
    struct todo_list_item_t fake[TODO_LIST_MAX];
    for (int i = 0; i < Todo_list_length; i++) {
        if (Todo_list[i].is_done != 1) {
            fake[spot] = Todo_list[i];
            spot++;
        } else {
            count++;
        }
    }
    Todo_list_length = Todo_list_length - count;
    int j = 0;
    while (j < Todo_list_length) {
        Todo_list[j] = fake[j];
        j++;
    }
    printf("Success! %d items removed!\n", count);

}

void optionFive(void) {
    printf(SAVE_FILE_HEADER);
    printf(INPUT_FILE_NAME);
    printf(GRAB_INPUT);
    char theFile[128];
    fgets_no_newline(theFile, 128, stdin);
    FILE *out_file = fopen(theFile, "w");
    for (int i = 0; i < Todo_list_length; i++) {
        fprintf(out_file, "%s\n", Todo_list[i].title);
        fprintf(out_file, "%s\n", Todo_list[i].description);
        fprintf(out_file, "%d\n", Todo_list[i].is_done);
        fprintf(out_file, "%d\n", Todo_list[i].due_day);
        fprintf(out_file, "%d\n", Todo_list[i].due_month);
        fprintf(out_file, "%d\n", Todo_list[i].due_year);
    }

    fclose(out_file);

}

void mainMenu (void) {
    while (1) {
        printf(MAIN_MENU_HEADER);
        printf(QUERY);
        printf(OPTIONS_LIST);
        printf(GRAB_INPUT);
        char input1[128];
        if (fgets(input1, 128, stdin) == NULL) {
            return;
        }
        int input = atoi(input1);
            if (input <= 0 || input > 6) {
                printf(INVALID_CHOICE);
            } else if (input == 1) {
                optionOne();
            } else if (input == 2) {
                optionTwo();
            } else if (input == 3) {
                optionThree();
            } else if (input == 4) {
                optionFour();
            } else if (input == 5) {
                optionFive();
            } else if (input == 6) {
                break;
            }
        }
}


int main(int argc, const char *argv[]) {
    if (argc <= 0 || argc > 2) {
        printf(ERROR_USAGE);
    } else if (argc == 1) {
        mainMenu();
        return 0;
    } else if (fopen(argv[1], "r") == NULL) {
        printf(FILE_NOT_FOUND);
        printf(" %s, ", argv[1]);
        printf(SECOND);
        return 0;
    } else {
        FILE *yourFile = fopen(argv[1], "r");
        while(read_todo_list_item(yourFile));
        fclose(yourFile);
        mainMenu();
        return 1;
        //append to the todo list
    }

}
