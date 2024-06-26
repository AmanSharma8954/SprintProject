#include "hdr.h"
#include "loggers.h"
 
void displayFileContent(char* filePath, char* result) {
    // Log that we are about to read the contents of the file
    LOG_INFO("Reading contents of file - %s", filePath);
 
    // Attempt to open the file for reading
    FILE* file = fopen(filePath, "r");
 
    // Check if the file was opened successfully
    if (file != NULL) {
        // Log that the file exists
        LOG_INFO("File exists - %s", "TRUE");
 
        // Append initial message to result
        strcat(result, "File exists\nContent of file:-\n");
        strcat(result, "========================================================================\n");
 
        // Read the file line by line and append to the result
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            strcat(result, buffer);
        }
 
        // Close the file once done reading
        fclose(file);
    } else {
        // If the file could not be opened, indicate it in the result
        strcpy(result, "File does not exist\n");
 
        // Log that the file does not exist (fatal error)
        LOG_FATAL("File exists - %s", "FALSE");
    }
}
