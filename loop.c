#include "shell.h"

/**
* shellLoop - main shell loop function
* @getInfo: info struct
* @argv: argument vector
* Return: 0 (success), 1 otherwise.
*/

int shellLoop(info_t *getInfo, char **argv)
{
    ssize_t ret = 0;
    int rett = 0;
    
    while (ret != -1 && rett != -2)
    {
        infoClear(getInfo);

        if (isInter(getInfo))
            _puts("$ ");

        _eputchar(FLUSH_BUFFER);
        ret = getInput(getInfo);

        if (ret != -1)
        {
            infoSet(getInfo, argv);
            rett = BuiltInCMD(getInfo);
            
            if (rett == -1)
                findCMD(getInfo);
        }
        else if (isInter(getInfo))
            _putchar('\n');

        infoFree(getInfo, 0);
    }

    writeHis(getInfo);
    infoFree(getInfo, 1);

    if (!isInter(getInfo) && getInfo->status)
        exit(getInfo->status);

    if (rett == -2)
    {
        if (getInfo->errorNumber == -1)
            exit(getInfo->status);

        exit(getInfo->errorNumber);
    }
    
    return (rett);
}

/**
* BuiltInCMD - a function that finds a built-in command
* @getInfo: info struct
* Return : success (0), failed (1), not found (-1), signals exit (-2).
*/

int BuiltInCMD(info_t *getInfo)
{
    int itr;
    int ret = -1;

    parameters_t parameters[] = {
        {"cd", _emuCD},
        {"exit", _emuExit},
        {"help", _emuHelp},
        {"alias", _emuAlias},
        {"history", _emuHistory},
        {"env", _curEnv},
        {"setenv", _initEnv},
        {"unsetenv", _remEnv},
        {NULL, NULL}
    };

    for (itr = 0; parameters[itr].command; itr++)
        if (_strcmp(getInfo->argumentv[0], parameters[itr].command) == 0)
        {
            getInfo->lineCount++;
            ret = parameters[itr].task(getInfo);
            break;
        }

    return (ret);
}

/**
* findCMD - a function which finds a command in the path
* @getInfo: info struct
* Return: void
*/

void findCMD(info_t *getInfo)
{
    char *dir = NULL;
    int itr, ktr;

    getInfo->directory = getInfo->argumentv[0];

    if (getInfo->lineCountF == 1)
    {
        getInfo->lineCount++;
        getInfo->lineCountF = 0;
    }
    
    for (itr = 0, ktr = 0; getInfo->arguments[itr]; itr++)
        if (!isDelimeter(getInfo->arguments[itr], " \t\n"))
            ktr++;
    
    if (!ktr)
        return;
    
    dir = findPath(getInfo, _getEnv(getInfo, "PATH="), getInfo->argumentv[0]);
    
    if (dir)
    {
        getInfo->directory = dir;
        forkCMD(getInfo);
    }
    else
    {
        if ((isInter(getInfo) || _getEnv(getInfo, "PATH=") 
            || getInfo->argumentv[0][0] == '/') 
            && isExe(getInfo, getInfo->argumentv[0]))
            forkCMD(getInfo);
        else if (*(getInfo->arguments) != '\n')
        {
            getInfo->status = 127;
            printError(getInfo, "not found\n");
        }
    }
}

/**
* forkCMD - a function that forks a thread to run a command
* @getInfo: info struct
* Return: void
*/

void forkCMD(info_t *getInfo)
{
    pid_t child;

    child = fork();

    if (child == -1)
    {
        perror("Error:");
        return;
    }

    if (child == 0)
    {
        if (execve(getInfo->directory, getInfo->argumentv,
            getEnv2(getInfo)) == -1)
        {
            infoFree(getInfo, 1);

            if (errno == EACCES)
                exit(126);

            exit(1);
        }
    }
    else
    {
        wait(&(getInfo->status));
        if (WIFEXITED(getInfo->status))
        {
            getInfo->status = WEXITSTATUS(getInfo->status);
            
            if (getInfo->status == 126)
                printError(getInfo, "Permission denied\n");
        }
    }
}