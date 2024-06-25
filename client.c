#include "hdr.h"
#include "client_function.h"
#include "macro.h"

int main() {
    // Create socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP);  // Server IP address
    serverAddr.sin_port = htons(PORT);                     // Server port

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    int choice;
    char buffer[MAX_BUFFER_SIZE];
    system("clear");
    while (1) {
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
        choice = get_int_input();

        send(clientSocket, &choice, sizeof(choice), 0);

        switch (choice) {
            case 1:
                system("clear");

                printf("==========================================================================\n");
                printf("You are looking for a file:\n");
                int case1SubChoice = 0;
                printf("    1. Enter with path\n");
                printf("    2. Enter without path\n");
                printf("    3. Go to Main\n");
                printf("==========================================================================\n");
                printf("    Enter Choice: ");
                case1SubChoice = get_int_input();

                if (case1SubChoice == 3) {
                    system("clear");
                    continue;
                }
                if (case1SubChoice != 1 && case1SubChoice != 2) {
                    printf("\nInvalid Input!\n");
                    continue;
                }

                char basePath[MAX_BUFFER_SIZE] = "";

                printf("Enter the path: ");
                if (case1SubChoice == 2) {
                    strcat(basePath, "/home2/user74/");
                }
                get_string_input(buffer, MAX_BUFFER_SIZE);
                strcat(basePath, buffer);
                send(clientSocket, basePath, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s\n", buffer);
                break;

            case 2:
                printf("Enter the string to be searched: ");
                get_string_input(buffer, MAX_BUFFER_SIZE);
                send(clientSocket, buffer, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                if (strcmp(buffer, "") == 0) {
                    printf("This string was not found in any file\n\n");
                    printf("Press any key to return to the main menu... ");
                    getchar(); // wait for user input
                    system("clear");
                    continue; // redirect to main menu
                } else {
                    printf("Server response:\n%s", buffer);
                    int case2SubChoice = 0;
                    printf("    1. View a file\n");
                    printf("    2. Do not view file\n");
                    printf("    3. Go to Main\n");
                    printf("    Enter Choice: ");
                    case2SubChoice = get_int_input();

                    if (case2SubChoice == 3) {
                        system("clear");
                        continue;
                    }

                    if (case2SubChoice == 1) {
                        printf("    Enter the path: ");
                        get_string_input(buffer, MAX_BUFFER_SIZE);
                        send(clientSocket, buffer, sizeof(buffer), 0);
                        recv(clientSocket, buffer, sizeof(buffer), 0);
                        printf("Server response:\n%s\n", buffer);
                    } else {
                        send(clientSocket, "", sizeof(buffer), 0);
                    }
                }
                break;

            case 3:
                printf("Enter the required path: ");
                get_string_input(buffer, MAX_BUFFER_SIZE);
                send(clientSocket, buffer, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s\n", buffer);
                break;

            case 4:
                system("clear");
                close(clientSocket);
                exit(EXIT_SUCCESS);

            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
                break;
        }

        printf("Press any key to continue... \n");
        getchar(); // wait for user input
        system("clear");
    }
    return 0;
}

