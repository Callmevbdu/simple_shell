#include "shell.h"

/**
 * _curEnv - function that prints the current environment
 * @info: arguments
 * Return: always (0)
*/

int _curEnv(info_t *info)
{
    stringPrint(info->environmentL);
    return (0);
}

/**
 * _getEnv - function that gets current environment
 * @getInfo: arguments
 * @n: variable name
 * Return: environment value
*/

char *_getEnv(info_t *getInfo, const char *n)
{
    list_t *current = getInfo->environmentL;
    char *ptr;

    while (current)
    {
        ptr = strstr(current->strings, n);
        if (ptr && *ptr)
            return (ptr);

        current = current->complete;
    }
    
    return (NULL);
}

/**
 * _initEnv - function that init an environment variable
 * @getInfo: arguments
 * Return: always (0)
*/

int _initEnv(info_t *getInfo)
{
    if (getInfo->argumentc != 3)
    {
        _eputs("Incorrect number of arguments.\n");
        return (1);
    }

    if (_setEnv(getInfo, getInfo->argumentv[1], getInfo->argumentv[2]))
        return (0);

    return (1);
}

/**
 * _remEnv - function that removes an environment variable
 * @getInfo: arguments
 * Return: always (0)
*/

int _remEnv(info_t *getInfo)
{
    int itr;

    if (getInfo->argumentc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }

    for (itr = 1; itr <= getInfo->argumentc; itr++)
        _unsetEnv(getInfo, getInfo->argumentv[itr]);

    return (0);
}