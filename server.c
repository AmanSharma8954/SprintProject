#include "hdr.h"                            //Customer header for definitions
#include "server_function.h"         //Server-specific functions 
#include "loggers.h"                     // LOG functions
#include "macro.h"                      //Macros and constants
 
int main() {
    // Logging an informational message about socket creation
    LOG_INFO("Creating Socket %s", "");
    // Creating a TCP socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        // Logging a fatal error if socket creation fails
        LOG_FATAL("Socket creation failed %s\n", "");
        exit(EXIT_FAILURE);
    }
 
    // Setting up server address structure
    LOG_INFO("Binding to port %s", "");
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
 
    // Binding socket to the specified port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        // Logging a fatal error if bind fails
        LOG_FATAL("Bind failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
 
    // Listening for incoming connections
    LOG_INFO("Listening for incoming connections %s", "");
    if (listen(serverSocket, 5) == -1) {
        // Logging a fatal error if listen fails
        LOG_FATAL("Listen failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
 
    // Informing that server is listening on a specific port
    LOG_INFO("Server listening on port %s...", "5678");
 
    // Accepting a client connection
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
        // Logging a fatal error if accept fails
        LOG_FATAL("Accept failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
 
    // Handling client requests in a loop
    while (1) {
        int choice = 0;
        int bytesReceived = recv(clientSocket, &choice, sizeof(choice), 0);
        if (bytesReceived <= 0) {
            // Logging a warning if failed to receive client's choice or connection closed
            LOG_WARN("Failed to receive choice from client or connection closed %s", "");
            break;
        }
        LOG_INFO("Received choice from client: %d", choice);
 
        char buffer[MAX_BUFFER_SIZE] = "";
        char result[MAX_BUFFER_SIZE] = "";
 
        switch (choice) {
            case 1:
                // Handling case 1: searching for a file
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    LOG_WARN("Failed to receive data for case 1 or connection closed %s", "");
                    break;
                }
                LOG_INFO("Received path from client: %s", buffer);
                searchForFile(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;
 
            case 2:
                // Handling case 2: searching for a string in a file
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    LOG_WARN("Failed to receive data for case 2 or connection closed %s", "");
                    break;
                }
                LOG_INFO("Received string to search from client: %s", buffer);
                searchForString(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                if (strcmp(result, "") == 0) {
                    strcpy(result, "This string was not found in any file\n");
                    send(clientSocket, result, sizeof(result), 0);
                    break;
                }
                // Additional handling for case 2: receiving file path and displaying content
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    LOG_WARN("Failed to receive file path or connection closed %s", "");
                    break;
                }
                LOG_INFO("Received file path from client: %s", buffer);
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;
 
            case 3:
                // Handling case 3: displaying content of a file
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived <= 0) {
                    LOG_WARN("Failed to receive data for case 3 or connection closed %s", "");
                    break;
                }
                LOG_INFO("Received file path from client: %s", buffer);
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;
 
            case 4:
                // Handling case 4: client request to exit
                LOG_INFO("Client requested to exit %s", "");
                close(clientSocket);
                close(serverSocket);
                exit(EXIT_SUCCESS);
 
            default:
                // Handling invalid input from client
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived > 0) {
                    LOG_WARN("Invalid input received from client: %s", buffer);
                }
                strcpy(result, "Invalid choice. Please enter a valid option.\n");
                send(clientSocket, result, sizeof(result), 0);
                break;
        }
    }
 
    // Closing client and server sockets after loop ends
    LOG_INFO("Closing socket now %s", "");
    close(clientSocket);
    LOG_INFO("Socket is now closed %s", "");
    close(serverSocket);
 
    return 0;
}
