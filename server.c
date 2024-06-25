#include "hdr.h"
#include "server_function.h"
#include "loggers.h"
#include "sf_displayFileContents.c"
#include "sf_searchForFile.c"
#include "sf_searchForString.c"

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
    serverAddr.sin_port = htons(5678);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        LOG_FATAL("Bind failed %s", "");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Listening for incoming connections %s", "");
    if (listen(serverSocket, 5) == -1) {
        LOG_FATAL("Listen failed %s", "");
        exit(EXIT_FAILURE);
    }

    LOG_INFO("Server listening on port %s...", "5678");
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == -1) {
        LOG_FATAL("Accept failed %s", "");
    }

    // Accept connections
    while (1) {

        // Receive client choice
        int choice;
        recv(clientSocket, &choice, sizeof(choice), 0);
        LOG_INFO("Choice of client - %d", choice);

        char buffer[MAX_BUFFER_SIZE] = "";
        char result[MAX_BUFFER_SIZE] = "";

        switch (choice) {

            case 1:
                recv(clientSocket, buffer, sizeof(buffer), 0);
                searchForFile(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;

            case 2:
                recv(clientSocket, buffer, sizeof(buffer), 0);
                searchForString(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                if (strcmp(result, "") == 0) {
                    break;
                }
                strcpy(result, "");
                recv(clientSocket, buffer, sizeof(buffer), 0);
                if (strcmp(buffer, "") == 0) {
                    break;
                }
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;

            case 3:
                 recv(clientSocket, buffer, sizeof(buffer), 0);
                displayFileContent(buffer, result);
                send(clientSocket, result, sizeof(result), 0);
                break;

            case 4:
                LOG_INFO("Exiting execution %s", "");
                close(clientSocket);
                close(serverSocket);
                exit(EXIT_SUCCESS);

            default:
                LOG_WARN("Invalid choice from client %s", "");

        }

    }

    LOG_INFO("Closing socket now %s", "");
    close(clientSocket);
    LOG_INFO("Socket is now closed %s", "");

    return 0;
}
                


