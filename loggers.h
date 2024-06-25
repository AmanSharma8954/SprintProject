#ifndef LOGGERS_H
#define LOGGERS_H

#define LOG_INFO(msg, arg) printf("[INFO] " msg "\n", arg);
#define LOG_WARN(msg, arg) printf("[WARN] " msg "\n", arg);
#define LOG_FATAL(msg, arg) printf("[FATAL] " msg "\n", arg);
#define LOG_DEBUG(msg, arg) printf("[DEBUG] " msg "\n", arg);

#endif
