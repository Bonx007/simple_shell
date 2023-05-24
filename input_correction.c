#include "shell.h"

int status;

int line_num;

char *shell_name;

/**
 * input_san - sanitizes input from the command line
 * @old_buf: buffer to be sanitized
 * @old_size: size of old buffer
 *
 * Return: the new, sanitized buffer
 */
char *input_san(char *old_buf, size_t *old_size) {
  char *new_buf = malloc(*old_size * 3);
  char *new_ptr = new_buf;
  char *old_ptr = old_buf;

  while (*old_ptr != '\0') {
    while (*old_ptr == ' ') {
      old_ptr++;
    }
    while (*old_ptr != ' ' && *old_ptr != ';' && *old_ptr != '|' &&
           *old_ptr != '&' && *old_ptr != '\0') {
      *new_ptr = *old_ptr;
      new_ptr++;
      old_ptr++;
    }
    while (*old_ptr == ' ') {
      old_ptr++;
    }
    if (new_ptr != new_buf && *old_ptr != '\0') {
      *new_ptr = ' ';
      new_ptr++;
    }

    if (*old_ptr == ';' || *old_ptr == '|' || *old_ptr == '&') {
      if (input_err_check(old_ptr) == FALSE) {
        *old_size = 0;
        break;
      }
      *new_ptr = *old_ptr;
      if (*old_ptr == ';') {
        new_ptr++;
        *new_ptr = ' ';
      } else if (*(old_ptr + 1) == *old_ptr) {
        if (new_ptr == new_buf) {
          err_message(old_ptr, NULL);
          *old_size = 0;
          break;
        }
        new_ptr++;
        *new_ptr = *old_ptr;
        new_ptr++;
        *new_ptr = ' ';
        old_ptr++;
      }
      new_ptr++;
      old_ptr++;
    }
  }
  *new_ptr = '\0';
  free(old_buf);
  return (new_buf);
}
