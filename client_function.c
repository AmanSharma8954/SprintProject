#include "hdr.h"  // Include the header file "hdr.h"

// Function to clear the stdin buffer
void clear_stdin() {
    int c;
    // Read characters until newline or EOF
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Function to get an integer input with validation
int get_int_input() {
    int input;
    // Loop until a valid integer is entered
    while (scanf("%d", &input) != 1) {
        clear_stdin();  // Clear the stdin buffer to avoid infinite loop
        printf("Invalid input! Please enter a valid integer: ");
    }
    clear_stdin();  // Clear the stdin buffer after successful input
    return input;   // Return the valid integer input
}

// Function to get string input
void get_string_input(char *buffer, int size) {
    // Read string input from stdin
    if (fgets(buffer, size, stdin) != NULL) {
        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

