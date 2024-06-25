void searchForFile(char* filePath, char* result) {
    LOG_INFO("Searching for a file in filesystem with filePath - %s", filePath);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        fclose(file);
        strcat(result, "Yes, the file exists!");
        LOG_INFO("File exists - %s", "TRUE");
    } else {
        strcat(result, "No, the file does not exist!");
        LOG_FATAL("File exists - %s", "FALSE");
    }
}
