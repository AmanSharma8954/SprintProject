#ifndef LOGGERS_H  // Check if LOGGERS_H is not defined
#define LOGGERS_H  // Define LOGGERS_H

#include <stdio.h>  // Include the standard I/O library for printf function

// Macro to log an informational message with a single argument
#define LOG_INFO(msg, arg) printf("[INFO] " msg "\n", arg);

// Macro to log a warning message with a single argument
#define LOG_WARN(msg, arg) printf("[WARN] " msg "\n", arg);

// Macro to log a fatal error message with a single argument
#define LOG_FATAL(msg, arg) printf("[FATAL] " msg "\n", arg);

// Macro to log a debug message with a single argument
#define LOG_DEBUG(msg, arg) printf("[DEBUG] " msg "\n", arg);

#endif // End of LOGGERS_H definition

