#include "shell.h"

/**
 * getHis - function that gets the history file
 * @getInfo: arguments
 * Return: history string
 */

char *getHis(info_t *getInfo)
{
    char *buffer, *directory;

    directory = _getEnv(getInfo, "HOME=");

    if (!directory)
        return (NULL);

    buffer = malloc(sizeof(char) * (_strlen(directory) +
                                    _strlen(HISTORY_FILE) + 2));

    if (!buffer)
        return (NULL);

    buffer[0] = 0;
    _strcpy(buffer, directory);
    _strcat(buffer, "/");
    _strcat(buffer, HISTORY_FILE);
    return (buffer);
}

/**
 * writeHis - function that creates, modifies the history file
 * @getInfo: arguments
 * Return: success (1), otherwise (-1)
 */

int writeHis(info_t *getInfo)
{
    ssize_t fDesc;
    list_t *current = NULL;
    char *fName = getHis(getInfo);

    if (!fName)
        return (-1);

    fDesc = open(fName, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(fName);

    if (fDesc == -1)
        return (-1);

    for (current = getInfo->history; current; current = current->complete)
    {
        _putsfDesc(current->strings, fDesc);
        _putfDesc('\n', fDesc);
    }

    _putfDesc(FLUSH_BUFFER, fDesc);
    close(fDesc);
    return (1);
}

/**
 * readHis - function that reads the history file
 * @getInfo: arguments
 * Return: success, otherwise (0)
 */

int readHis(info_t *getInfo)
{
    ssize_t fDesc, fLeng, fSize = 0;
    struct stat status;
    char *buffer = NULL, *fName = getHis(getInfo);
    int itr, count = 0, end = 0;

    if (!fName)
        return (0);

    fDesc = open(fName, O_RDONLY);
    free(fName);

    if (fDesc == -1)
        return (0);

    if (!fstat(fDesc, &status))
        fSize = status.st_size;

    if (fSize < 2)
        return (0);

    buffer = malloc(sizeof(char) * (fSize + 1));

    if (!buffer)
        return (0);

    fLeng = read(fDesc, buffer, fSize);
    buffer[fSize] = 0;

    if (fLeng <= 0)
        return (free(buffer), 0);

    close(fDesc);

    for (itr = 0; itr < fSize; itr++)
        if (buffer[itr] == '\n')
        {
            buffer[itr] = 0;
            buildHis(getInfo, buffer + end, count++);
            end = itr + 1;
        }

    if (end != itr)
        buildHis(getInfo, buffer + end, count++);

    free(buffer);
    getInfo->historyCount = count;

    while (getInfo->historyCount-- >= HISTORY_MAX)
        removeNode(&(getInfo->history), 0);

    numberHis(getInfo);

    return (getInfo->historyCount);
}

/**
 * buildHis - function that builds the history file
 * @getInfo: arguments
 * @buffer: buffer
 * @count: line count
 * Return: 0.
 */

int buildHis(info_t *getInfo, char *buffer, int count)
{
    list_t *current = NULL;

    if (getInfo->history)
        current = getInfo->history;

    addNodeEnd(&current, buffer, count);

    if (!getInfo->history)
        getInfo->history = current;

    return (0);
}

/**
 * numberHis - function that re-numbers the history file linkedlist
 * @getInfo: arguments
 * Return: history count (modifed).
 */

int numberHis(info_t *getInfo)
{
    list_t *current = getInfo->history;
    int itr = 0;

    while (current)
    {
        current->number = itr++;
        current = current->complete;
    }

    return (getInfo->historyCount = itr);
}