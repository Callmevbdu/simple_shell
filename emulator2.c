#include "shell.h"

/**
 * _emuAlias - the manual of the function 'Alias' in the Shell
 * @getInfo: arguments
 * Return: success (0)
*/

int _emuAlias(info_t *getInfo)
{
    int itr = 0;
    char *ptr = NULL;
    list_t *current = NULL;

    if (getInfo->argumentc == 1)
    {
        current = getInfo->alias;

        while (current)
        {
            emuPrintAlias(current);
            current = current->complete;
        }

        return (0);
    }

    for (itr = 1; getInfo->argumentv[itr]; itr++)
    {
        ptr = _strchr(getInfo->argumentv[itr], '=');

        if (ptr)
            emuSetAlias(getInfo, getInfo->argumentv[itr]);
        else
            emuPrintAlias(listPrefix(getInfo->alias, getInfo->argumentv[itr], '='));
    }

    return (0);
}

/**
 * emuSetAlias - function that creates alias in the Shell
 * @getInfo: arguments
 * @s: string
 * Return: success (0)
*/

int emuSetAlias(info_t *getInfo, char *s)
{
    char *ptr;

    ptr = _strchr(s, '=');

    if (!ptr)
        return (1);

    if (!*++ptr)
        return (emuUnAlias(getInfo, s));
    
    emuUnAlias(getInfo, s);
    return (addNodeEnd(&(getInfo->alias), s, 0) == NULL); 
}

/**
 * emuUnAlias - function that removes alias from the Shell
 * @getInfo: arguments
 * @s: string
 * Return: success (0)
*/

int emuUnAlias(info_t *getInfo, char *s)
{
    char *ptr, ch;
    int end;

    ptr = _strchr(s, '=');

    if (!ptr)
        return (1);

    ch = *ptr;
    *ptr = 0;

    end = removeNode(&(getInfo->alias),
        getIndex(getInfo->alias, listPrefix(getInfo->alias, s, -1)));
    
    *ptr = ch;

    return(end);
}

/**
 * emuPrintAlias - function that prints the alias in the Shell
 * @current: alias node
 * Return: successfully exited (0); 1 otherwise.
*/

int emuPrintAlias(list_t *current)
{
    char *ptr = NULL, *n = NULL;

    if (current)
    {
        ptr = _strchr(current->strings, '=');

        for (n = current->strings; n <= ptr; n++)
            _putchar(*n);

       _putchar('\'');
       _puts(ptr + 1);
       _puts("'\n");
       return (0);
    }

    return (1);
}