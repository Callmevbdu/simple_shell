#include "shell.h"

/**
 * memFree - clears a string of strings
 * @ptr: string
*/

void memFree(char **ptr)
{
    char **str = ptr;

    if (!ptr)
        return;

    while (*ptr)
        free(*ptr++);

    free(str);
}

/**
 * _memAlloc - a function that re-allocates a memory block
 * @ptr: a pointer to block
 * @old: size of the previous
 * @new: size of the new
*/

void *_memAlloc(void *ptr, unsigned int old, unsigned int new)
{
    char *m;

    if (!ptr)
        return (malloc(new));
    
    if (!new)
        return (free(ptr), NULL);

    if (new == old)
        return (ptr);

    m = malloc(new);

    if (!m)
        return (NULL);

    old = old < new ? old : new;

    while (old--)
        m[old] = ((char *)ptr) [old];
    
    free(ptr);
    return (m);
}

/**
 * _memSet - a function that fills memory with a constant byte
 * @str: input string
 * @buffer: input character
 * @num: input number of bytes
 * Return: pointer to @str
*/

char *_memSet(char *str, char buffer, unsigned int num)
{
	unsigned int var;

	for (var = 0; var < num; var++)
	{
		str[var] = buffer;
	}

	return (str);
}

/**
 * ptrFree - function that clears a pointer
 * @ptr: pointer concerned
 * Return: 1 (success), 0 otherwise.
*/

int ptrFree(void **ptr)
{
    if (ptr && *ptr)
    {
        free(*ptr);
        *ptr = NULL;
        return (1);
    }

    return (0);
}