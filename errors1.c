void _eputs(char *str) {
  // Prints an input string to stderr.

  if (!str) {
    // If str is null, return.
    return;
  }

  int i = 0;

  while (str[i] != '\0') {
    // Iterate through the string and print each character.
    _eputchar(str[i]);
    i++;
  }
}

int _eputchar(char c) {
  // Writes the character c to stderr.

  static int i;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    // If c is BUF_FLUSH or the buffer is full, write the buffer to stderr.
    write(2, buf, i);
    i = 0;
  }

  if (c != BUF_FLUSH) {
    // If c is not BUF_FLUSH, add c to the buffer.
    buf[i++] = c;
  }

  return 1;
}

int _putfd(char c, int fd) {
  // Writes the character c to the file descriptor fd.

  static int i;
  static char buf[WRITE_BUF_SIZE];

  if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE) {
    // If c is BUF_FLUSH or the buffer is full, write the buffer to fd.
    write(fd, buf, i);
    i = 0;
  }

  if (c != BUF_FLUSH) {
    // If c is not BUF_FLUSH, add c to the buffer.
    buf[i++] = c;
  }

  return 1;
}

int _putsfd(char *str, int fd) {
  // Prints an input string to the file descriptor fd.

  int i = 0;

  if (!str) {
    // If str is null, return 0.
    return 0;
  }

  while (*str) {
    // Iterate through the string and print each character.
    i += _putfd(*str++, fd);
  }

  return i;
}
