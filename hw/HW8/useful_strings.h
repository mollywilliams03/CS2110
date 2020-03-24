// This file will contain a few string macros that you will find EXTREMELY helpful in your program
// Feel free to edit.

/* General */
#define GRAB_INPUT "> "

/* Menu Screen and Initialization */

#define MAIN_MENU_HEADER "================================== TO-DO LIST ==================================\n\n"
#define OPTIONS_LIST  "1) Print my To-do List\n2) Add a To-do List Item\n3) Mark an item completed\n4) Remove all completed items\n5) Save as\n6) Quit\n\n"
#define INVALID_CHOICE "Invalid choice!\n"
#define QUERY "What would you like to do?\n\n"
#define FILE_NOT_FOUND "ERROR: File,"
#define SECOND "does not exist!\n"
#define ERROR_USAGE "ERROR: Usage: todolist (save_file)\n"

/* Print All To-Do List Items Screen */
#define TODO_LIST_HEADER "-------------------------------- YOUR TO-DO LIST -------------------------------\n\n"
#define LINE_BREAK " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n"
#define COMPLETED "Completed!\n"

/* Add To-Do List Items */
#define ADD_TO_LIST_HEADER "------------------------------- ADD TO TO-DO LIST ------------------------------\n\n"
#define LIST_MAX "You need to drop some classes...\n"
#define ADD_TO_LIST "Type in on separate lines in this order:\n\n- Title\n- Description\n- If it is completed (1 or 0)\n- Due Day\n- Due Month\n- Due Year\n\n"

/* Mark Item Completed */
#define MARK_ITEM_COMPLETED_HEADER "------------------------------ MARK ITEM COMPLETED -----------------------------\n\n"
#define MARK_ITEM_USER_INPUT "Enter the index of the item you want to mark completed:\n\n"

/* Remove Item */
#define REMOVE_ITEM_HEADER "---------------------------- REMOVE COMPLETED ITEMS ----------------------------\n\n"

/* Save Into File */
#define SAVE_FILE_HEADER "--------------------------------- SAVE FILE AS ---------------------------------\n\n"
#define INPUT_FILE_NAME "Please enter the file name you would like to save to up to 127 characters in length:\n\n"
