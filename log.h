#ifndef AAG031_LOGGER_H__
#define AAG031_LOGGER_H__

#include <stdbool.h>
#include <stdio.h>

/*private constant*/
#ifdef LOG_LIB_MAIN
const  unsigned int MAX_PREFIX_STRING_SIZE = 8;
char * const PREFIX_LOG_RECORD [] = {"FATAL", "ERROR", "INFO", "WARN", "DEBUG", "TRACE"};
FILE *log_stream = NULL;
char log_file_name[FILENAME_MAX + 1];
unsigned int log_level;
#else
extern FILE *log_stream;
extern char log_file_name[FILENAME_MAX + 1];
extern unsigned int log_level;
#endif

// max size of record for logging
#define MAX_LOG_RECORD_SIZE  4096
/* ERROR CODES*/
#ifdef LOG_LIB_MAIN
const unsigned long LOG_OP_RC_SUCCESS  = 0;
const unsigned long LOG_OP_RC_CANNOT_OPEN_FILE = 1000;
const unsigned long LOG_OP_RC_CANNOT_WRITE_TO_FILE = 1001;
const unsigned long LOG_OP_RC_CANNOT_FLUSH_FILE  = 1002;
const unsigned long LOG_OP_RC_CANNOT_CLOSE_FILE  = 1003;
#else
extern const unsigned long LOG_OP_RC_SUCCESS;
extern const unsigned long LOG_OP_RC_CANNOT_OPEN_FILE;
extern const unsigned long LOG_OP_RC_CANNOT_WRITE_TO_FILE;
extern const unsigned long LOG_OP_RC_CANNOT_FLUSH_FILE;
extern const unsigned long LOG_OP_RC_CANNOT_CLOSE_FILE;
#endif

// LOG levels
typedef enum {
    FATAL = 0,
    ERROR,
    INFO,
    WARN,
    DEBUG,
    TRACE
} t_log_level;

/*Implementation of saving record in log. this internal function, shall not be used by client */
int write_msg_impl(FILE * stream, const char *const fmt_str, const t_log_level r_log_level, const char *const file_name,const char *const func_name, const int nline, ...);
/* client API */
/* start logging session */
int init_logging(const char * const p_log_file_name, const bool is_append, const t_log_level log_level);

/* stop logging session */
void stop_logging();

/* change log level */
void set_log_level(const t_log_level p_log_level);

/* get record prefix */
char * get_record_prefix(t_log_level level);

void create_log_record(char * record, const t_log_level r_log_level, const char *const file_name, const char *const func_name, const int nline);

/* client macro */


#define TRACE(fmt, ...)    write_msg_impl(log_stream, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)

#define DEBUG(fmt, ...)    write_msg_impl(log_stream, fmt , DEBUG,  __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)

#define INFO(fmt, ...)     write_msg_impl(log_stream, fmt , INFO,   __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)

#define WARNING(fmt, ...)  write_msg_impl(log_stream, fmt , WARN,   __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)

#define ERROR(fmt, ...)    write_msg_impl(log_stream, fmt,  ERROR, __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)

#define FATAL(fmt, ...)    write_msg_impl(log_steam, fmt , FATAL, __FILE__, __func__, __LINE__,  __VA_ARGS__); \
                           write_msg_impl(stdout, fmt , TRACE,  __FILE__, __func__, __LINE__,  __VA_ARGS__)


#define NEW_LINE()             write_msg_to_log_impl("\n")
#endif  // AAG031_LOGGER_H__
