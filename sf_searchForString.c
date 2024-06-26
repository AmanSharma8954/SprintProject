#include "hdr.h" // Include the header file for standard functions and definitions.
#include "loggers.h" // Include the header file for logging functions.
 
// Function to search for a string within a given file.
void searchInFile(const char* filePath, const char* searchString, char* result) {
    // Open the file in read mode.
    FILE* file = fopen(filePath, "r");
    if (file != NULL) { // Check if the file opened successfully.
        char buffer[256]; // Buffer to store lines read from the file.
        // Read each line of the file.
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            // Check if the search string is found in the current line.
            if (strstr(buffer, searchString) != NULL) {
                LOG_INFO("String found in file - %s", filePath); // Log the occurrence of the string.
                // Append the file path to the result.
                strcat(result, filePath);
                strcat(result, "\n");
                break; // Stop searching once the string is found.
            }
        }
        fclose(file); // Close the file after reading.
    } else {
        LOG_FATAL("Unable to open %s", "file"); // Log an error if the file can't be opened.
    }
}
 
// Function to search for a string within all files in a directory (recursively).
void searchInDirectory(const char* dirPath, const char* searchString, char* result) {
    // Open the directory.
    DIR* directory = opendir(dirPath);
    if (directory == NULL) { // Check if the directory opened successfully.
        LOG_FATAL("Unable to open %s", "directory"); // Log an error if the directory can't be opened.
        return;
    }
    struct dirent* entry; // Structure to hold directory entries.
    // Read each entry in the directory.
    while ((entry = readdir(directory)) != NULL) {
        // Skip hidden files and special directories "." and "..".
        if (entry->d_name[0] != '.' && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char fullPath[PATH_MAX]; // Buffer to store the full path of the current entry.
            // Construct the full path of the entry.
            snprintf(fullPath, sizeof(fullPath), "%s/%s", dirPath, entry->d_name);
            if (entry->d_type == DT_DIR) { // Check if the entry is a directory.
                // Skip the root and a specific directory ("/home2").
                if (strcmp(entry->d_name, "/") == 0 || strcmp(entry->d_name, "/home2") == 0)
                    continue;
                // Recursively search in the subdirectory.
                searchInDirectory(fullPath, searchString, result);
            } else if (entry->d_type == DT_REG) { // Check if the entry is a regular file.
                // Search for the string in the file.
                searchInFile(fullPath, searchString, result);
            }
        }
    }
    closedir(directory); // Close the directory after reading.
}
 
// Function to initiate the search for a string in the file system.
void searchForString(const char* searchString, char* result) {
    LOG_INFO("Searching for the string '%s' in the filesystem", searchString); // Log the start of the search.
    // Start searching in the root directory "/home2".
    searchInDirectory("/home2", searchString, result);
}
