#include "shell.h"

/**
 * isExe - function which checks if file is executable
 * @getInfo: info struct
 * @directory: file directory
 * Return: if executable (1), 0 otherwise.
*/

int isExe(info_t *getInfo, char *directory)
{
    struct stat status;

    (void)getInfo;

    if (!directory || stat(directory, &status))
        return (0);

    if (status.st_mode & S_IFREG)
        return (1);

    return (0);
}

/**
 * charDuplicate - function which duplicates characters
 * @directory: file directory
 * @init: index of initialising
 * @end: index of ending
 * Return: pointer to buffer
*/

char *charDuplicate(char *directoy, int init, int end)
{
    static char buffer[1024];
    int idx = 0, kdx = 0;

    for (kdx = 0, idx = init; idx < end; idx++)
        if (directoy[idx] != ':')
            buffer[kdx++] = directoy[idx];

    buffer[kdx] = 0;
    return (buffer);
}

/**
 * findPath - function which searches for command's path
 * @getInfo: struct INFO
 * @directory: string
 * @command: command to find
 * Return: the path (success), NULL otherwise.
*/

char *findPath(info_t *getInfo, char *directory, char *command)
{
    int itr = 0, current = 0;
    char *dir;

    if (!directory)
        return (NULL);

    if ((_strlen(command) > 2) && strstr(command, "./"))
    {
        if (isExe(getInfo, command))
            return (command);
    }

    while (1)
    {
        if (!directory[itr] || directory[itr] == ':')
        {
            dir = charDuplicate(directory, current, itr);

            if (!*dir)
                _strcat(dir, command);
            else
            {
                _strcat(dir, "/");
                _strcat(dir, command);
            }
            
            if (isExe(getInfo, dir))
                return (dir);

            if (!directory[itr])
                break;

            current = itr;
        }

        itr++;
    }

    return (NULL);
}