#include "shell.h"

/**
 * _strncpy - a function that copies a string
 * @firstStr: input string 1
 * @secondStr: input string 2
 * @num: number of bytes from @src
 * Return: full string
*/

char *_strncpy(char *firstStr, char *secondStr, int num)
{
	int itr, jtr;
	char *str = firstStr;

	itr = 0;

	while (secondStr[itr] != '\0' && itr < num - 1)
	{
		firstStr[itr] = secondStr[itr];
		itr++;
	}

	if (itr < num)
	{
		jtr = itr;
		
		while (jtr < num)
		{
			firstStr[jtr] = '\0';
			jtr++;
		}
	}
	return (str);
}

/**
 * _strncat - a function that concatenates two string
 * @firstStr: input string 1
 * @secondStr: input string 2
 * @num: number of bytes from @src
 * Return: concatenated two strings.
*/

char *_strncat(char *firstStr, char *secondStr, int num)
{
	int itr, jtr;
	char *str = firstStr;

	itr = 0;
	jtr = 0;

	while (firstStr[itr] != '\0')
	{
		itr++;
	}

	while (secondStr[jtr] != '\0' && jtr < num)
	{
		firstStr[itr] = secondStr[jtr];
		itr++;
		jtr++;
	}

	if (jtr < num)
	{
		firstStr[itr] = '\0';
	}

	return (str);
}

/**
 * _strchr - a function that locates a character in a string
 * @str: input string pointer
 * @ch: character to be found
 * Return: the string pointer
*/

char *_strchr(char *str, char ch)
{

	do {
		if (*str == ch)
		{
			return (str);
		}
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * strtow - a function that splits strings into words
 * @str: input string
 * @del: delimeter input string
 * Return: array of strings (success), "NULL" otherwise. 
*/

char **strtow(char *str, char *del)
{
	int w, x, y, z, num = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!del)
		del = " ";

	for (w = 0; str[w] != '\0'; w++)
		if (!isDelimeter(str[w], del) && (isDelimeter(str[w + 1], del) || !str[w + 1]))
			num++;

	if (num == 0)
		return (NULL);

	c = malloc((1 + num) * sizeof(char *));

	if (!c)
		return (NULL);
	
	for (w = 0, x = 0; x < num; x++)
	{
		while (isDelimeter(str[w], del))
			w++;

		y = 0;
	
		while (!isDelimeter(str[w + y], del) && str[w + y])
			y++;
	
		c[x] = malloc((y + 1) * sizeof(char));
	
		if (!c[x])
		{
			for (y = 0; y < x; y++)
				free(c[y]);
			
			free(c);
			return (NULL);
		}

		for (z = 0; z < y; z++)
			c[x][z] = str[w++];
	
		c[x][z] = 0;
	}
	c[x] = NULL;

	return (c);
}

/**
 * strtwo - a function that splits strings into words
 * @str: input string
 * @del: delimeter string
 * Return: array of strings (success), "NULL" otherwise. 
*/

char **strtwo(char *str, char del)
{
	int w, x, y, z, num = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);

	for (w = 0; str[w] != '\0'; w++)
		if ((str[w] != del && str[w + 1] == del) || 
			(str[w] != del && !str[w + 1]) || str[w + 1] == del)
			num++;

	if (num == 0)
		return (NULL);

	c = malloc((1 + num) * sizeof(char *));

	if (!c)
		return (NULL);
	
	for (w = 0, x = 0; x < num; x++)
	{
		while (str[w] == del && str[w] != del)
			w++;
		
		y = 0;
	
		while (str[w + y] != del && str[w + y] && str[w + y] != del)
			y++;
	
		c[x] = malloc((y + 1) * sizeof(char));
	
		if (!c[x])
		{
			for (y = 0; y < x; y++)
				free(c[y]);

			free(c);
			return (NULL);
		}

		for (z = 0; z < y; z++)
			c[x][z] = str[w++];
	
		c[x][z] = 0;
	}
	c[x] = NULL;
	return (c);
}