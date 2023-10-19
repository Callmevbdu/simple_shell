#include "shell.h"

/**
 * strstr - a function that searches for a string in the Shell
 * @path: where to search
 * @str: the string to find
 * Return: the string, "NULL" otherwise.
*/

char *strstr(const char *path, const char *str)
{
	while (*str)
	{
		if (*str++ != *path++)
			return (NULL);
	} 
	return ((char *) path);
}

/**
 * _strcat - a function that concatenates two string
 * @firstStr: input string 1
 * @secondStr: input string 2
 * Return: concatenated string
*/

char *_strcat(char *firstStr, char *secondStr)
{
	char *full = firstStr;

	while (*firstStr)
		firstStr++;

	while (*secondStr)
		*firstStr++ = *secondStr++;

	*firstStr = *secondStr;

	return (full);
}

/**
 * _strcpy - a function that copies a string
 * @firstStr: a string input
 * @secondStr: a string input
 * Return: pointer to secondStr
*/

char *_strcpy(char *firstStr, char *secondStr)
{
	int itr = 0;

	if (firstStr == secondStr || secondStr == 0)
	{
		return (firstStr);
	}

	while (secondStr[itr])
	{
		firstStr[itr] = secondStr[itr];
		itr++;
	}

	firstStr[itr] = 0;
	return (firstStr);
}

/**
 * _strdup - a function that duplicates a sting
 * @str: a string input
 * Return: a pointer to the duplicated string (success).
*/

char *_strdup(const char *str)
{
	int size = 0;
	char *m;

	if (str == NULL)
		return (NULL);

	while (*str++)
		size++;

	m = malloc(sizeof(char) * (size + 1));

	if (!m)
		return (NULL);

	for (size++; size--;)
			m[size] = *--str;
	return (m);
}