#include "shell.h"

/**
 * _strlen - a function that returns the lenght of a string
 * @str: string input
 * Return: Lenght of a string
*/

int _strlen(char *str)
{
	int count = 0;

    if (!str)
    {
        return (0);
    }
    
	while (*str++)
		count++;
	return (count);
}

/**
 * _strcmp - a function that compares two strings
 * @firstStr: input string 1
 * @secondStr: input string 2
 * Return: negative if s1 is smaller than s2, positive if the opposite, 0 if the same.
*/

int _strcmp(char *firstStr, char *secondStr)
{
	while (*firstStr && *secondStr)
	{
		if (*firstStr != *secondStr)
		{
			return (*firstStr - *secondStr);
		}
		firstStr++;
		secondStr++;
	}

	if (*firstStr == *secondStr)
		return (0);
	else
		return (*firstStr < *secondStr ? -1 : 1);
}

/**
 * _putfDesc - function that prints a character in given file descriptor
 * @ch: string input
 * @fDesc: file descriptor
 * Return: 1 success, -1 otherwise.
*/

int _putfDesc(char ch, int fDesc)
{
    static int itr;
    static char buffer[WRITE_BUFFER];

    if (ch == FLUSH_BUFFER || itr >= WRITE_BUFFER)
    {
        write(fDesc, buffer, itr);
        itr = 0;
    }

    if (ch != FLUSH_BUFFER)
        buffer[itr++] = ch;
    
    return (1);
}

/**
 * _putsfDesc - function that prints a string
 * @st: string input
 * @fDesc: file descriptor
 * Return: number of characters
*/

int _putsfDesc(char *st, int fDesc)
{
    int itr = 0;

    if (!st)
        return (0);

    while (*st)
    {
        itr += _putfDesc(*st++, fDesc);
    }
    
    return (itr);
}