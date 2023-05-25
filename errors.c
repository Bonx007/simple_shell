#include "shell.h"

/**
 * Prints an input string to stderr.
 *
 * @param str The string to be printed.
 */
void _eputs(char *str) {
  int i = 0;

  if (!str) {
    return;
  }

  while (str[i] != '\0') {
    _eputchar(str[i]);
    i++;
  }
}

/**
 * Writes the character c to stderr.
 *
 * @param c The character to print.
 *
 * @return On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c) {
  static int i;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    write(2, buf, i);
    i = 0;
  }

  if (c != BUF_FLUSH) {
    buf[i++] = c;
  }

  return 1;
}

/**
 * Writes the character c to the file descriptor fd.
 *
 * @param c The character to print.
 * @param fd The file descriptor to write to.
 *
 * @return On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd) {
  static int i;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    write(fd, buf, i);
    i = 0;
  }

  if (c != BUF_FLUSH) {
    buf[i++] = c;
  }

  return 1;
}

/**
 * Prints an input string to the file descriptor fd.
 *
 * @param str The string to be printed.
 * @param fd The file descriptor to write to.
 *
 * @return The number of characters printed.
 */
int _putsfd(char *str, int fd) {
  int i = 0;

  if (!str) {
    return 0;
  }

  while (*str) {
    i += _putfd(*str++, fd);
  }

  return i;
}

