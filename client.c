#include "hdr.h"
#include "server_function.h"
#include "loggers.h"
#include "sf_displayFileContents.c"
#include "sf_searchForFile.c"
#include "sf_searchForString.c"

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
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address
    serverAddr.sin_port = htons(5678);                     // Server port

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    int choice;
    char buffer[MAX_BUFFER_SIZE];
    system("clear");
    while (1) {
	a:
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
        
	scanf("%d", &choice);

        send(clientSocket, &choice, sizeof(choice), 0);

        switch (choice) {
                case 1: 
		system("clear");

	        printf("==========================================================================\n");
        
		printf("Your are looking for a file:\n");
		int case1SubChoice = 0;
                printf("    1. Enter with path\n");
                printf("    2. Enter without path\n");
		printf("    3. Go to Main\n");
		b:
	        printf("==========================================================================\n");
        
		printf("    Enter Choice: ");
                scanf("%d", &case1SubChoice);
  		if( case1SubChoice == 3 ) {
			system("clear");
			goto a;
		}
		if( case1SubChoice != 1 && case1SubChoice != 2 && case1SubChoice != 3 ){
	printf("\nInvalid Input!\n");
	goto b;
		}	
               	char basePath[MAX_BUFFER_SIZE] = "";
		
                printf("Enter the path: ");
                if (case1SubChoice == 2) {
                    strcat(basePath, "/home2/user74/");
                }
                scanf("%s", buffer);
                strcat(basePath, buffer);
                send(clientSocket, basePath, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s\n",buffer);
//		print(buffer);
                break;
            case 2:
                printf("Enter the string to be searched: ");
                getchar();
                scanf("%[^\n]s", buffer);
                send(clientSocket, buffer, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s", buffer);
                if (strcmp(buffer, "") == 0) {
                    printf("This string was not found in any file\n\n");
                    break;
                }
                int case2SubChoice = 0;
                printf("    1. View a file\n");
                printf("    2. Do not view file\n");
                printf("    Enter Choice: ");

                scanf("%d", &case2SubChoice);
                getchar();
                if (case2SubChoice == 1) {
                    printf("    Enter the path: ");
                    scanf("%[^\n]s", buffer);
                    send(clientSocket, buffer, sizeof(buffer), 0);
                    recv(clientSocket, buffer, sizeof(buffer), 0);
                    printf("Server response:\n%s\n", buffer);
                } else {
                    send(clientSocket, "", sizeof(buffer), 0);
                }
                break;
            case 3:
                printf("Enter the required path: ");
                getchar();
                scanf("%[^\n]s", buffer);
                send(clientSocket, buffer, sizeof(buffer), 0);
                recv(clientSocket, buffer, sizeof(buffer), 0);
                printf("Server response:\n%s\n", buffer);
		
                break;
      	case 4:  
		system("clear");
		      close(clientSocket);
		exit(EXIT_SUCCESS);

            default:
                printf("Invalid choice.\n");
        }

       	
	printf("Press any key to continue... \n");
	getchar();
	getchar();	
	system("clear");

    
	
    }
    return 0;
}
