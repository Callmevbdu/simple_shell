#include "shell.h"

/**
 * infoClear - function which clears items in info_t
 * @getInfo: address
*/

void infoClear(info_t *getInfo)
{
    getInfo->arguments = NULL;
    getInfo->argumentv = NULL;
    getInfo->directory = NULL;
    getInfo->argumentc = 0;
}

/**
 * infoFree - function which frees items in info_t
 * @getInfo: address
 * @full: set "true" if you want to free all items
*/

void infoFree(info_t *getInfo, int full)
{
    memFree(getInfo->argumentv);

    getInfo->argumentv = NULL;
    getInfo->directory = NULL;

    if (full)
    {
        if (!getInfo->commandBuffer)
            free(getInfo->arguments);

        if (getInfo->environmentL)
            listFree(&(getInfo->environmentL));
        
        if (getInfo->history)
            listFree(&(getInfo->history));

        if (getInfo->alias)
            listFree(&(getInfo->alias));

        memFree(getInfo->environmentC);
            getInfo->environmentC = NULL;

        ptrFree((void **)getInfo->commandBuffer);

        if (getInfo->readFileDescriptor > 2)
            close(getInfo->readFileDescriptor);

        _putchar(FLUSH_BUFFER);
    }
}

/**
 * infoSet - function which sets item in info_t
 * @getInfo: address
 * @argv: argument
*/

void infoSet(info_t *getInfo, char **argv)
{
    int itr = 0;

    getInfo->fileName = argv[0];

    if (getInfo->arguments)
    {
        getInfo->argumentv = strtow(getInfo->arguments, " \t");

        if (!getInfo->argumentv)
        {
            getInfo->argumentv = malloc(sizeof(char *) * 2);

            if (getInfo->argumentv)
            {
                getInfo->argumentv[0] = _strdup(getInfo->arguments);
                getInfo->argumentv[1] = NULL;
            }
        }

        for (itr = 0; getInfo->argumentv && getInfo->argumentv[itr]; itr++)
            getInfo->argumentc = itr;

        replaceAlias(getInfo);
        replaceVar(getInfo);
    }
}