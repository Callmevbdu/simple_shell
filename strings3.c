#include "shell.h"

/**
 * _puts - a function that prints a string
 * @str: a string input
 * Return: nothing
*/

void _puts(char *str)
{
	int itr = 0;

	if (!str)
		return;

	while (str[itr] != '\0')
	{
		_putchar(str[itr]);
		itr++;
	}
}

/**
 * _eputs - function that prints a string
 * @s: string input
*/

void _eputs(char *s)
{
    int itr = 0;

    if (!s)
        return;

    while (s[itr] != '\0')
    {
        _eputchar(s[itr]);
        itr++;
    }
}

/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/

int _putchar(char ch)
{
	static int itr;
	static char buffer[WRITE_BUFFER];

	if (ch == FLUSH_BUFFER || itr >= WRITE_BUFFER)
		{
			write(1, buffer, itr);
			itr = 0;
		}

	if (ch != FLUSH_BUFFER)
		buffer[itr++] = ch;

	return (1);
}

/**
 * _eputchar - function that prints a character in stderr
 * @ch: string input
 * Return: 1 success, -1 otherwise.
*/

int _eputchar(char ch)
{
    static int itr;
    static char buffer[WRITE_BUFFER];

    if (ch == FLUSH_BUFFER || itr >= WRITE_BUFFER)
    {
        write(2, buffer, itr);
        itr = 0;
    }

    if (ch != FLUSH_BUFFER)
        buffer[itr++] = ch;
    
    return (1);
}