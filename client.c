#include "hdr.h"                // Custom header for definitions
#include "client_function.h"    // Client-specific functions
#include "macro.h"              // Macros and constants
 
int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0); // Create TCP socket
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
 
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP);  // Server IP address
    serverAddr.sin_port = htons(PORT);           // Server port
 
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }
 
    int choice;
    char buffer[MAX_BUFFER_SIZE];
    system("clear"); // Clear the console screen
 
    while (1) { // Main loop for displaying menu and processing user input
        // Display menu options
        printf("==========================================================================\n");
        printf("                       Remote Search Engine                               \n");
        printf("==========================================================================\n");
        printf("Options:\n");
        printf("1. Search for a file\n");
        printf("2. Search for a string in the filesystem\n");
        printf("3. Display the content of a file\n");
        printf("4. Exit\n");
        printf("==========================================================================\n");
 
        printf("Enter your choice: ");
        choice = get_int_input(); // Get user's menu choice
        send(clientSocket, &choice, sizeof(choice), 0); // Send user's choice to server
 
        switch (choice) { // Handle different menu options
            case 1:
                system("clear"); // Clear screen for file search submenu
                printf("==========================================================================\n");
                printf("You are looking for a file:\n");
                int case1SubChoice = 0;
                printf("    1. Enter with path\n");
                printf("    2. Enter without path\n");
                printf("    3. Go to Main\n");
                printf("==========================================================================\n");
                printf("    Enter Choice: ");
                case1SubChoice = get_int_input(); // Get user's subchoice
 
                if (case1SubChoice == 3) { // Return to main menu if user chooses
                    system("clear");
                    continue;
                }
                if (case1SubChoice != 1 && case1SubChoice != 2) { // Handle invalid input
                    printf("\nInvalid Input!\n");
                    continue;
                }
 
                char basePath[MAX_BUFFER_SIZE] = "";
 
                printf("Enter the path: ");
                if (case1SubChoice == 2) {
                    strcat(basePath, "/home2/user74/"); // Default path if subchoice is 2
                }
                get_string_input(buffer, MAX_BUFFER_SIZE); // Get user-provided path
                strcat(basePath, buffer); // Append user-provided path to basePath
                send(clientSocket, basePath, sizeof(buffer), 0); // Send path to server
                recv(clientSocket, buffer, sizeof(buffer), 0); // Receive server's response
                printf("Server response:\n%s\n", buffer); // Print server's response
                break;
 
            case 2:
                printf("Enter the string to be searched: ");
                get_string_input(buffer, MAX_BUFFER_SIZE); // Get search string from user
                send(clientSocket, buffer, sizeof(buffer), 0); // Send search string to server
                recv(clientSocket, buffer, sizeof(buffer), 0); // Receive server's response
                if (strcmp(buffer, "") == 0) { // If server response is empty
                    printf("This string was not found in any file\n\n");
                    printf("Press any key to return to the main menu... ");
                    getchar(); // Wait for user input
                    system("clear"); // Clear screen and return to main menu
                    continue;
                } else {
                    printf("Server response:\n%s", buffer); // Print server's response
                    int case2SubChoice = 0;
                    printf("    1. View a file\n");
                    printf("    2. Do not view file\n");
                    printf("    3. Go to Main\n");
                    printf("    Enter Choice: ");
                    case2SubChoice = get_int_input(); // Get user's subchoice
 
                    if (case2SubChoice == 3) { // Return to main menu if user chooses
                        system("clear");
                        continue;
                    }
 
                    if (case2SubChoice == 1) {
                        printf("    Enter the path: ");
                        get_string_input(buffer, MAX_BUFFER_SIZE); // Get file path from user
                        send(clientSocket, buffer, sizeof(buffer), 0); // Send file path to server
                        recv(clientSocket, buffer, sizeof(buffer), 0); // Receive server's response
                        printf("Server response:\n%s\n", buffer); // Print server's response
                    } else {
                        send(clientSocket, "", sizeof(buffer), 0); // Send empty string to server
                    }
                }
                break;
 
            case 3:
                printf("Enter the required path: ");
                get_string_input(buffer, MAX_BUFFER_SIZE); // Get file path from user
                send(clientSocket, buffer, sizeof(buffer), 0); // Send file path to server
                recv(clientSocket, buffer, sizeof(buffer), 0); // Receive server's response
                printf("Server response:\n%s\n", buffer); // Print server's response
                break;
 
            case 4:
                system("clear"); // Clear screen
                close(clientSocket); // Close client socket
                exit(EXIT_SUCCESS); // Exit program successfully
 
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }
 
        printf("Press any key to continue... \n");
        getchar(); // Wait for user input before showing menu again
        system("clear"); // Clear screen
    }
    return 0;
}
