#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

static FILE *log_file = NULL;

void open_log_file() {
    log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("Unable to open log file");
        exit(EXIT_FAILURE);
    }
}

void close_log_file() {
    if (log_file != NULL) {
        fclose(log_file);
    }
}

void log_message(log_level_t level, const char *format, ...) {
    if (log_file == NULL) {
        return;
    }

    time_t now = time(NULL);
    char *time_str = ctime(&now);
    time_str[strlen(time_str) - 1] = '\0';

    va_list args;
    va_start(args, format);

    fprintf(log_file, "[%s] ", time_str);

    switch(level) {
        case LOG_DEBUG:
            fprintf(log_file, "[DEBUG] ");
            break;
        case LOG_INFO:
            fprintf(log_file, "[INFO] ");
            break;
        case LOG_ERROR:
            fprintf(log_file, "[ERROR] ");
            break;
    }

    vfprintf(log_file, format, args);
    fprintf(log_file, "\n");
    fflush(log_file);

    va_end(args);
}