#include "hdr.h"     // Include the header file "hdr.h"
#include "loggers.h" // Include the header file "loggers.h" for logging macros

// Function to search for a file and update the result string based on its existence
void searchForFile(char* filePath, char* result) {
    // Log the start of the file search
    LOG_INFO("Searching for a file in filesystem with filePath - %s", filePath);

    // Try to open the file in read mode
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        // If the file exists, close the file and update the result string
        fclose(file);
        strcat(result, "Yes, the file exists!");
        // Log that the file exists
        LOG_INFO("File exists - %s", "TRUE");
    } else {
        // If the file does not exist, update the result string
        strcat(result, "No, the file does not exist!");
        // Log that the file does not exist with a fatal error message
        LOG_FATAL("File exists - %s", "FALSE");
    }
}

