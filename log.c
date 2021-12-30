//-------------------------------------------------------------------------------------------------
// <copyright file="log.c" company="House of Badger">
// Copyright (c) EMC Corporation. All rights reserved.
// </copyright>
// History
// ------------------------------------
// Date       Who     Info
// ------------------------------------
// 06/20/2013 Alexander Gorlov initial version
//-------------------------------------------------------------------------------------------------

#include <assert.h>
#include <libgen.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#define LOG_LIB_MAIN 1
#include "log.h"

/* client API
   start logging session
   init logging system, create file if required
   @param[in] p_log_file_name the name of log file, if exist it will be overwritten if is no exist will be created
   @param[in] p_is_append - should be log file created or or overwriten
   @param[in] p_is_append - log level
   @return error code.
   */
int init_logging(const char *const p_log_file_name, const bool p_is_append, const t_log_level p_log_level) {
  assert(log_file_name != NULL);
  log_level = p_log_level;

  strncpy(log_file_name, p_log_file_name, FILENAME_MAX);
  log_file_name[FILENAME_MAX] = '\0';
  char flags[2];
  flags[1] = '\0';

  if (p_is_append) {
    flags[0] = 'a';
  } else {
    flags[0] = 'w';
  }

  log_stream = fopen(log_file_name, flags);
  if (log_stream == NULL) {
    return LOG_OP_RC_CANNOT_OPEN_FILE;
  }

  return LOG_OP_RC_SUCCESS;
}

/* stop logging session. flush buffer and close log file */
void stop_logging() {
  int rc; // return code
  rc = fclose(log_stream);
  if (rc != 0) {
    printf("Flushing to file failed\n");
    return;
  }

  return;
}

/*saving record implementation. client should use corresponded macros */
int write_msg_impl(FILE * stream, const char *const fmt_str, const t_log_level r_log_level, const char *const file_name,
                          const char *const func_name, const int nline, ...) {
  va_list ap;
  int rc; // function return code

  if (r_log_level > log_level) {
    return LOG_OP_RC_SUCCESS;
  }

  char record[MAX_LOG_RECORD_SIZE];
  create_log_record(&record[0], r_log_level, file_name, func_name, nline);

  rc = fprintf(stream, "%s ", record);
  if (rc < 0) {
    printf("Cannot save record in log");
    return LOG_OP_RC_CANNOT_WRITE_TO_FILE;
  }

  va_start(ap, nline);
  rc = vfprintf(stream, fmt_str, ap);
  fprintf(stream, "\n");
  if (rc < 0) {
    printf("Cannot save record in log");
    return LOG_OP_RC_CANNOT_WRITE_TO_FILE;
  }
  va_end(ap);

  return LOG_OP_RC_SUCCESS;
}

void create_log_record(char * record, const t_log_level r_log_level, const char *const file_name, const char *const func_name, const int nline) {
  char *record_prefix = get_record_prefix(r_log_level);
  time_t timeval; // time stamp
  char * time_str;
  timeval = time(NULL);
  time_str = ctime(&timeval);
  time_str [strlen(time_str)-1] = '\0';
  char *file_name_short = basename((char *)file_name);

  snprintf(record, MAX_LOG_RECORD_SIZE,  "%s : %s ==>  %s:%s:%d ", time_str, record_prefix, file_name_short, func_name, nline);
  return;
}


void set_log_level(const t_log_level p_log_level) {
  INFO("Current log level %d\n", log_level);
  log_level = p_log_level;
  INFO("Current log level %d\n", log_level);
}

char *get_record_prefix(t_log_level level) { return PREFIX_LOG_RECORD[level]; }
