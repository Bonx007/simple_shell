#include "shell.h"

char *_memset(char *s, char b, unsigned int n) {
  unsigned int i;

  for (i = 0; i < n; i++) {
    s[i] = b;
  }
  return (s);
}

/**
 * Fills the first `n` bytes of the memory area pointed to by `s` with the constant byte `b`.
 */

void ffree(char **pp) {
  char **a = pp;

  if (!pp) {
    return;
  }
  while (*pp) {
    free(*pp++);
  }
  free(a);
}

/**
 * Frees the memory allocated for a string of strings.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size) {
  char *p;

  if (!ptr) {
    return (malloc(new_size));
  }
  if (!new_size) {
    return (free(ptr), NULL);
  }
  if (new_size == old_size) {
    return (ptr);
  }

  p = malloc(new_size);
  if (!p) {
    return (NULL);
  }

  old_size = old_size < new_size ? old_size : new_size;
  while (old_size--) {
    p[old_size] = ((char *)ptr)[old_size];
  }
  free(ptr);
  return (p);
}

/**
 * Reallocates a block of memory. The new size of the block is specified by `new_size`. If `new_size` is 0, the function frees the memory allocated for the block and returns NULL. If `new_size` is the same as the old size of the block, the function returns the pointer to the block. Otherwise, the function allocates a new block of memory with the specified size and copies the contents of the old block to the new block. The old block is then freed. The function returns a pointer to the new block.
 */
