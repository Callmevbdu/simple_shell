#include "shell.h"

/**
 * _emuExit - function that quits the Shell
 * @getInfo: arguments
 * Return: successfully exited (0)
*/

int _emuExit(info_t *getInfo)
{
    int check;

    if (getInfo->argumentv[1])
    {
        check = _atoiError(getInfo->argumentv[1]);

        if (check == -1)
        {
            getInfo->status = 2;
            printError(getInfo, "Illegal number: ");
            _eputs(getInfo->argumentv[1]);
            _eputchar('\n');
            return (1);
        }

        getInfo->errorNumber = _atoiError(getInfo->argumentv[1]);
        return (-2);
    }

    getInfo->errorNumber = -1;
    return (-2);
}

/**
 * _emuCD - function that changes directory in the Shell
 * @getInfo: arguments
 * Return: success (0)
*/

int _emuCD(info_t *getInfo)
{
    char *str, *directory, buffer[1024];
    int changeDir;

    str = getcwd(buffer, 1024);

    if (!str)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!getInfo->argumentv[1])
    {
        directory = _getEnv(getInfo, "HOME=");

        if (!directory)
            changeDir = chdir((directory = _getEnv(getInfo, "PWD=")) ? directory : "/");
        else
            changeDir = chdir(directory);
    }

    else if (_strcmp(getInfo->argumentv[1], "-") == 0)
    {
        if (!_getEnv(getInfo, "OLDPWD="))
        {
            _puts(str);
            _putchar('\n');
            return (1);
        }

        _puts(_getEnv(getInfo, "OLDPWD=")), _putchar('\n');
        changeDir = chdir((directory = _getEnv(getInfo, "OLDPWD=")) ? directory : "/");
    }
    else
        changeDir = chdir(getInfo->argumentv[1]);
    
    if (changeDir == -1)
    {
        printError(getInfo, "Can't change directory to ");
        _eputs(getInfo->argumentv[1]), _eputchar('\n');
    }
    else
    {
        _setEnv(getInfo, "OLDPWD", _getEnv(getInfo, "PWD="));
        _setEnv(getInfo, "PWD", getcwd(buffer, 1024));
    }

    return (0);
}

/**
 * _emuHelp - function that shows help in the Shell
 * @getInfo: arguments
 * Return: success (0)
*/

int _emuHelp(info_t *getInfo)
{
    char **arr;

    arr = getInfo->argumentv;
    _puts("help call works. Function not yet implemented \n");

    if (0)
        _puts(*arr);

    return (0);
}

/**
 * _emuHistory - function that shows history of the Shell
 * @getInfo: arguments
 * Return: success (0)
*/

int _emuHistory(info_t *getInfo)
{
    listPrint(getInfo->history);
    return (0);
}