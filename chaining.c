#include "shell.h"

/** 
 * checkChain - function that checks if we can continue chaining based on
 * last task
 * @getInfo: info struct
 * @buffer: buffer
 * @current: buffer current address
 * @start: buffer start address
 * @length: buffer length
 * Return: Void
*/

void checkChain(info_t *getInfo, char *buffer, size_t *current, size_t start, size_t length)
{
    size_t itr = *current;

    if (getInfo->commandBufferType == IS_AND)
    {
        if (getInfo->status)
        {
            buffer[start] = 0;
            itr = length;
        }
    }

    if (getInfo->commandBufferType == IS_OR)
    {
        if (!getInfo->status)
        {
            buffer[start] = 0;
            itr = length;
        }
    }

    *current = itr;
}

/**
* isChain - function that checks if the current input is a chaining delim
* @getInfo: info struct
* @buffer: buffer
* @current: current position in buffer
* Return: if input is a delimeter (1), otherwise (0).
*/

int isChain(info_t *getInfo, char *buffer, size_t *current)
{
    size_t itr = *current;

    if (buffer[itr] == '|' && buffer[itr + 1] == '|')
    {
        buffer[itr] = 0;
        itr++;
        getInfo->commandBufferType = IS_OR;
    }
    else if (buffer[itr] == '&' && buffer[itr + 1] == '&')
    {
        buffer[itr] = 0;
        itr++;
        getInfo->commandBufferType = IS_AND;
    }
    else if (buffer[itr] == ';')
    {
        buffer[itr] = 0;
        getInfo->commandBufferType = IS_CHAIN;
    }
    else
        return (0);

    *current = itr;
    return (1);
}

/**
* replaceString - function that replaces a string
* @current: old string
* @new: new string
* Return: success (1), otherwise (0).
*/

int replaceString(char **current, char *new)
{
    free(*current);
    *current = new;
    return (1);
}

/**
* replaceVar - function that replaces variables
* @getInfo: info struct
* Return: 1 (success), otherwise 0
*/

int replaceVar(info_t *getInfo)
{
    int itr = 0;
    list_t *current;

    for (itr = 0; getInfo->argumentv[itr]; itr++)
    {
        if (getInfo->argumentv[itr][0] != '$' || !getInfo->argumentv[itr][1])
            continue;

        if (!_strcmp(getInfo->argumentv[itr], "$?"))
        {
            replaceString(&(getInfo->argumentv[itr]), 
                _strdup(convertNum(getInfo->status, 10, 0)));
            continue;
        }

        if (!_strcmp(getInfo->argumentv[itr], "$$"))
        {
            replaceString(&(getInfo->argumentv[itr]),
                _strdup(convertNum(getpid(), 10, 0)));
            continue;
        }

        current = listPrefix(getInfo->environmentL, &getInfo->argumentv[itr][1], '=');

        if (current)
        {
            replaceString(&(getInfo->argumentv[itr]), 
                _strdup(_strchr(current->strings, '=') + 1));
            continue;
        }

        replaceString(&getInfo->argumentv[itr], _strdup(""));
    }

    return (0);
}

/**
* replaceAlias - function that replaces an alias
* @getInfo: info struct
* Return: 1 (success), otherwise 0.
*/

int replaceAlias(info_t *getInfo)
{
    list_t *current;
    int itr;
    char *ptr;

    for (itr = 0; itr < 10; itr++)
    {
        current = listPrefix(getInfo->alias, getInfo->argumentv[0], '=');

        if (!current)
            return (0);

        free(getInfo->argumentv[0]);
        ptr = _strchr(current->strings, '=');
        
        if (!ptr)
            return (0);

        ptr = _strdup(ptr + 1);

        if (!ptr)
            return (0);

        getInfo->argumentv[0] = ptr;
    }
    return (1);
}