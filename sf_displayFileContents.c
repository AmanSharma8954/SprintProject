
void displayFileContent(char* filePath, char* result) {
    LOG_INFO("Reading contents of file - %s", filePath);
    FILE* file = fopen(filePath, "r");
    if (file != NULL) {
        LOG_INFO("File exists - %s", "TRUE");
        strcat(result, "File exists\nContent of file:-\n");
	strcat(result,"========================================================================\n");
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            strcat(result, buffer);
        }
        fclose(file);
    } else {
        strcpy(result, "File does not exist\n");
        LOG_FATAL("File exists - %s", "FALSE");
    }
}
