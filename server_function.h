#ifndef SERVER_FUNCTIONS_H  // Check if SERVER_FUNCTIONS_H is not defined
#define SERVER_FUNCTIONS_H  // Define SERVER_FUNCTIONS_H

// Function to search for a file with a given name in a directory
// Parameters:
// - directory: The directory to search in
// - filename: The name of the file to search for
void searchForFile(char* directory, char* filename);

// Function to search for a string within a specific file
// Parameters:
// - filepath: The path of the file to search in
// - searchString: The string to search for
// - result: Buffer to store the search result
void searchInFile(const char* filepath, const char* searchString, char* result);

// Function to search for a string in all files within a directory
// Parameters:
// - directory: The directory to search in
// - searchString: The string to search for
// - result: Buffer to store the search result
void searchInDirectory(const char* directory, const char* searchString, char* result);

// Function to search for a string globally (implementation-defined scope)
// Parameters:
// - searchString: The string to search for
// - result: Buffer to store the search result
void searchForString(const char* searchString, char* result);

// Function to display the content of a file
// Parameters:
// - filepath: The path of the file to display
// - result: Buffer to store the file content
void displayFileContent(char* filepath, char* result);

#endif // End of SERVER_FUNCTIONS_H definition

