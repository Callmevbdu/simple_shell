#include "shell.h"

/**
 * listLength - function that calculates the number of elements in a lists
 * @h: linked list to traverse
 * Return: number of nodes
 */

size_t listLength(const list_t *h)
{
    size_t itr = 0;

    while (h)
    {
        h = h->complete;
        itr++;
    }

    return (itr);
}

/**
 * listFree - function that frees a linked list
 * @hptr: pointer address to be freed
 */

void listFree(list_t **hptr)
{
    list_t *current, *new, *h;

    if (!hptr || !*hptr)
        return;

    h = *hptr;
    current = h;

    while (current)
    {
        new = current->complete;
        free(current->strings);
        free(current);
        current = new;
    }

    *hptr = NULL;
}

/**
 * listString - function that converts a list into array of strings
 * @h: pointer
 * Return: array of strings
 */

char **listString(list_t *h)
{
    list_t *current = h;
    size_t itr = listLength(h), jtr;

    char *st;
    char **st2;

    if (!h || !itr)
        return (NULL);

    st2 = malloc(sizeof(char *) * (itr + 1));

    if (!st2)
        return (NULL);

    for (itr = 0; current; current = current->complete, itr++)
    {
        st = malloc(_strlen(current->strings) + 1);

        if (!st)
        {
            for (jtr = 0; jtr < itr; jtr++)
                free(st2[jtr]);

            free(st2);
            return (NULL);
        }
        st = _strcpy(st, current->strings);
        st2[itr] = st;
    }

    st2[itr] = NULL;
    return (st2);
}

/**
 * stringPrint - function that prints string element of linked list
 * @h: pointer
 * Return: size of the list
 */

size_t stringPrint(const list_t *h)
{
    size_t itr = 0;

    while (h)
    {
        _puts(h->strings ? h->strings : "(nil)");
        _puts("\n");
        h = h->complete;
        itr++;
    }
    return (itr);
}

/**
 * getIndex - function that collects the index of a node
 * @h: linked list to traverse
 * @current: pointer to node
 * Return: the index of a node.
 */

ssize_t getIndex(list_t *h, list_t *current)
{
    size_t itr = 0;

    while (h)
    {
        if (h == current)
            return (itr);

        h = h->complete;
        itr++;
    }

    return (-1);
}