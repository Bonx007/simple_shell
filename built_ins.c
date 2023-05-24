#include "shell.h"

int status;

/**
 * _setenv - sets an environmental variable
 * @name: name of the variable
 * @value: value to set the variable to
 *
 * Return: 0 on success
 */
int _setenv(const char *name, const char *value) {
  if (value == NULL) {
    write(STDERR_FILENO, "setenv: no value given\n");
    status = 2;
    return (SKIP_FORK);
  }

  char *buffer = str_concat(name, "=");
  char *element_ptr = get_array_element(environ, buffer);
  char *buf_tmp = str_concat(buffer, value);
  free(buffer);
  buffer = buf_tmp;

  if (element_ptr == NULL) {
    int len = list_len(environ, NULL);
    char **new_environ = array_cpy(environ, len + 1);
    new_environ[len - 1] = buffer;
    new_environ[len] = NULL;
    free_array(environ);
    environ = new_environ;
  } else {
    int len = list_len(environ, name);
    free(environ[len]);
    environ[len] = buffer;
  }

  status = 0;
  return (SKIP_FORK);
}

/**
 * _unsetenv - deletes an environmental variable
 * @name: name of variable
 *
 * Return: 0 if successful
 */
int _unsetenv(const char *name) {
  char *buffer = str_concat(name, "=");
  int len = list_len(environ, buffer);
  free(buffer);

  if (len == -1) {
    write(STDERR_FILENO, "unsetenv: variable not found\n");
    status = 2;
    return (SKIP_FORK);
  }

  char **env_ptr = environ + len;
  free(*env_ptr);

  while (*(env_ptr + 1) != NULL) {
    *env_ptr = *(env_ptr + 1);
    env_ptr++;
  }

  *env_ptr = NULL;

  status = 0;
  return (SKIP_FORK);
}

/**
 * change_dir - changes the current working directory
 * @name: name of directory to change to
 *
 * Return: 0 if successful
 */
int change_dir(char *name) 
{
  char old_path_buffer[PATH_MAX];
  getcwd(old_path_buffer, PATH_MAX);

  if (name == NULL) {
    char *home = get_array_element(environ, "HOME=");
    if (home == NULL) {
      status = 2;
      err_message("cd", name);
      return (SKIP_FORK);
    }

    int rc = chdir(home + 5);
    if (rc != -1) {
      _setenv("PWD", home + 5);
    }
  } else if (strcmp(name, "-") == 0) {
    char *oldpwd = get_array_element(environ, "OLDPWD=");
    if (oldpwd == NULL) {
      status = 2;
      err_message("cd", name);
      return (SKIP_FORK);
    }

    int rc = chdir(oldpwd + 7);
    if (rc != -1) {
      write(STDOUT_FILENO, oldpwd, _strlen(oldpwd));
      write(STDOUT_FILENO, "\n", 1);
      _setenv("PWD", oldpwd);
    }
  } else {
    int rc = chdir(name);
    if (rc != -1) {
      _setenv("PWD", getcwd(new_path_buffer, PATH_MAX));
    }
  }

  if (rc == -1) 
 {
    status = 2;
    err_message("cd", name);
    return (SKIP_FORK);
 }
