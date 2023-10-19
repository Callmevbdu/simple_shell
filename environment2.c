#include "shell.h"

/**
 * popEnv - function that populates an environment
 * @getInfo: arguments
 * Return: always (0)
*/

int popEnv(info_t *getInfo)
{
    list_t *current = NULL;
    size_t itr;

    for (itr = 0; environ[itr]; itr++)
    {
        addNodeEnd(&current, environ[itr], 0);
    }
    
    getInfo->environmentL = current;
    return (0);
}

/**
 * getEnv2 - function that returns a copy of a string array
 * @getInfo: arguments
 * Return: always (0)
*/

char **getEnv2(info_t *getInfo)
{
    if (!getInfo->environmentC || getInfo->environmentChanged)
    {
        getInfo->environmentC = listString(getInfo->environmentL);
        getInfo->environmentChanged = 0;
    }

    return (getInfo->environmentC);
}

/**
 * unsetEnv - function that unset an environment variable
 * @getInfo: arguments
 * @v: variable
 * Return: 1 (success), 0 otherwise.
*/

int _unsetEnv(info_t *getInfo, char *v)
{
    list_t *current = getInfo->environmentL;
    size_t itr = 0;
    char *ptr;

    if (!current || !v)
        return (0);

    while (current)
    {
        ptr = strstr(current->strings, v);

        if (ptr && *ptr == '=')
        {
            getInfo->environmentChanged = removeNode(&(getInfo->environmentL), itr);
            itr = 0;
            current = getInfo->environmentL;
            continue;
        }

        current = current->complete;
        itr++;
    }

    return (getInfo->environmentChanged);
}

/**
 * setEnv - function that sets a new environment variable
 * @getInfo: arguments
 * @v: variable
 * @val: value
 * Return: (0) always.
*/

int _setEnv(info_t *getInfo, char *v, char *val)
{
    char *buffer = NULL;
    list_t *current;
    char *ptr;

    if (!v || !val)
        return(0);

    buffer = malloc(_strlen(v) + _strlen(val) + 2);

    if (!buffer)
        return (1);

    _strcpy(buffer, v);
    _strcat(buffer, "=");
    _strcat(buffer, val);
    current = getInfo->environmentL;

    while (current)
    {
        ptr = strstr(current->strings, v);

        if (ptr && *ptr == '=')
        {
            free(current->strings);
            current->strings = buffer;
            getInfo->environmentChanged = 1;
            return (0);
        }

        current = current->complete;
    }
    
    addNodeEnd(&(getInfo->environmentL), buffer, 0);
    free(buffer);
    getInfo->environmentChanged = 1;
    return (0);
}