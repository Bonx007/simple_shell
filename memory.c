#inclide "shell.h"

int free_pointer(void **ptr) 
{
  /* The `free_pointer()` function frees a pointer and sets the address to NULL.
   * The function takes one argument: a pointer to the pointer to free.
   */
  if (ptr && *ptr) {
    /* Check if the pointer is not NULL and if the pointer to the pointer is not NULL.
     * If either of these conditions are not met, the function returns 0.
     */
    {
      free(*ptr);
    }
    /* Call the `free()` function to free the memory pointed to by the pointer to the pointer.
     */
    {
      *ptr = NULL;
    }
    /* Set the pointer to the pointer to NULL.
     */
    return (1);
  }
  /* If both conditions are met, the function returns 1.
   */
  return (0);
}
