#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path) {
  struct stat st;

  /* Ignore `info` argument. */

  if (!path || stat(path, &st)) {
    return 0;
  }

  /* Check if the file is executable. */
  if (st.st_mode & S_IFREG) {
    return 1;
  }
  return 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop) {
  static char buf[1024];
  int i = 0, k = 0;

  /* Create a new buffer of size 1024. */
  for (k = 0, i = start; i < stop; i++) {
    /* Check if the character is a colon. */
    if (pathstr[i] != ':') {
      /* Add the character to the new buffer. */
      buf[k++] = pathstr[i];
    }
  }
  buf[k] = 0;
  return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd) {
  int i = 0, curr_pos = 0;
  char *path;

  /* Check if the PATH string is NULL. */
  if (!pathstr) {
    return NULL;
  }

  /* Check if the command starts with "./". */
  if ((_strlen(cmd) > 2) && starts_with(cmd, "./")) {
    /* Check if the command is executable. */
    if (is_cmd(info, cmd)) {
      return cmd;
    }
  }

  /* Loop through the PATH string. */
  while (1) {
    /* Check if the current character is a colon or the end of the string. */
    if (!pathstr[i] || pathstr[i] == ':') {
      /* Create a new path by appending the command to the current path. */
      path = dup_chars(pathstr, curr_pos, i);
      if (*path) {
        _strcat(path, "/");
        _strcat(path, cmd);
      } else {
        _strcat(path, cmd);
      }

      /* Check if the new path is executable. */
      if (is_cmd(info, path)) {
        return path;
      }

      /* Check if we've reached the end of the PATH string. */
      if (!pathstr[i]) {
        break;
      }

      /* Set the current position to the next character. */
      curr_pos = i + 1;
    }
    i++;
  }
  return NULL;
}
