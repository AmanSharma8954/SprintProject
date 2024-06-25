#include "hdr.h"
// Function to clear the stdin buffer
void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Function to get an integer input with validation
int get_int_input() {
    int input;
    while (scanf("%d", &input) != 1) {
        clear_stdin();
        printf("Invalid input! Please enter a valid integer: ");
    }
    clear_stdin();
    return input;
}

// Function to get string input
void get_string_input(char *buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';  // Remove newline character
    }
}


