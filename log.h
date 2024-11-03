#ifndef LOG_H
#define LOG_H

#include <stdarg.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_ERROR
} log_level_t;

void log_message(log_level_t level, const char *format, ...);
void open_log_file(void);
void close_log_file(void);

#endif