#include "hdr.h"
#include "server_function.h"
#include "loggers.h"
#include "macro.h"

int main() {

    LOG_INFO("Creating Socket %s", "");
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        LOG_FATAL("Socket creation failed %s\n", "");
        exit(EXIT_FAILURE);
    }

    // Bind to a specific port
    LOG_INFO("Binding to port %s", "");
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        LOG_FATAL("Bind failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Listening for incoming connections %s", "");
    if (listen(serverSocket, 5) == -1) {
        LOG_FATAL("Listen failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Server listening on port %s...", "5678");
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
        LOG_FATAL("Accept failed %s", "");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Accept connections
    while (1) {
        int choice = 0;
        int bytesReceived = recv(clientSocket, &choice, sizeof(choice), 0);
        if (bytesReceived <= 0) {
            LOG_WARN("Failed to receive choice from client or connection closed %s", "");
            break;
        }
        LOG_INFO("Received choice from client: %d", choice);

        char buffer[MAX_BUFFER_SIZE] = "";
        char result[MAX_BUFFER_SIZE] = "";

        switch (choice) {
            case 1:
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
                LOG_INFO("Client requested to exit %s", "");
                close(clientSocket);
                close(serverSocket);
                exit(EXIT_SUCCESS);

            default:
                bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
                if (bytesReceived > 0) {
                    LOG_WARN("Invalid input received from client: %s", buffer);
                }
                strcpy(result, "Invalid choice. Please enter a valid option.\n");
                send(clientSocket, result, sizeof(result), 0);
                break;
        }
    }

    LOG_INFO("Closing socket now %s", "");
    close(clientSocket);
    LOG_INFO("Socket is now closed %s", "");
    close(serverSocket);

    return 0;
}

