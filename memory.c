#include "shell.h"

/**
 * bfree - frees a pointer
 * @ptr: pointer to free
 *
 * Return: 1 if done, and 0 if not.
 */
int bfree(void **ptr)
{
	if (*ptr && ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
