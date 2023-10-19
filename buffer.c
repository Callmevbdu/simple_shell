#include "shell.h"

/**
* inputBuffer - function that gets buffers chained commands
* @getInfo: info struct
* @buffer: buffer
* @length: variable length
* Return: total of read bytes.
*/

ssize_t inputBuffer(info_t *getInfo, char **buffer, size_t *length)
{
    ssize_t x = 0;
    size_t z = 0;

    if (!*length)
    { 
        free(*buffer);
        *buffer = NULL;
        signal(SIGINT, handleSignal);

#if USE_GETLINE
        x = getline(buffer, &z, stdin);
#else
        x = _getLine(getInfo, buffer, &z);
#endif

        if (x > 0)
        {
            if ((*buffer)[x - 1] == '\n')
            {
                (*buffer)[x - 1] = '\0';
                x--;
            }

            getInfo->lineCountF = 1;
            unComment(*buffer);
            buildHis(getInfo, *buffer, getInfo->historyCount++);
            {
                *length = x;
                getInfo->commandBuffer = buffer;
            }
        }
    }

    return (x);
}

/**
* readBuffer - function that reads a buffer
* @getInfo: info struct
* @buffer: buffer
* @size: buffer size
* Return: size.
*/

ssize_t readBuffer(info_t *getInfo, char *buffer, size_t *size)
{
    ssize_t ret = 0;

    if (*size)
        return (0);

    ret = read(getInfo->readFileDescriptor, buffer, READ_BUFFER);

    if (ret >= 0)
        *size = ret;

    return (ret);
}

/**
* getInput - function which gets the previous line
* @getInfo: info struct
* Return: total of read bytes.
*/

ssize_t getInput(info_t *getInfo)
{
    ssize_t ret = 0;
    static char *buffer;
    static size_t itr, jtr, length;
    char **bufferPtr = &(getInfo->arguments), *ptr;

    _putchar(FLUSH_BUFFER);
    ret = inputBuffer(getInfo, &buffer, &length);

    if (ret == -1)
        return (-1);

    if (length)
    {
        jtr = itr; 
        ptr = buffer + itr; 
        checkChain(getInfo, buffer, &jtr, itr, length);

        while (jtr < length) 
        {
            if (isChain(getInfo, buffer, &jtr))
                break;

            jtr++;
        }

        itr = jtr + 1;
        
        if (itr >= length) 
        {
            itr = length = 0;
            getInfo->commandBufferType = IS_NORMAL;
        }
        
        *bufferPtr = ptr;
        return (_strlen(ptr));
    }
    
    *bufferPtr = buffer;
    return (ret);
}

/**
* getLine - function that gets STDIN next line.
* @getInfo: information struct
* @ptr: address of pointer input
* @leng: size of ptr buffer
* Return: @set
*/

int _getLine(info_t *getInfo, char **ptr, size_t *leng)
{
    static char buffer[READ_BUFFER];
    static size_t itr, lgth;
    ssize_t ret = 0, set = 0;
    size_t var;
    char *p = NULL, *pp = NULL, *ch;

    p = *ptr;

    if (p && leng)
        set = *leng;

    if (itr == lgth)
        itr = lgth = 0;

    ret = readBuffer(getInfo, buffer, &lgth);

    if (ret == -1 || (ret == 0 && lgth == 0))
        return (-1);

    ch = _strchr(buffer + itr, '\n');
    var = ch ? 1 + (unsigned int)(ch - buffer) : lgth;
    pp = _memAlloc(p, set, set ? set + var : var + 1);

    if (!pp)
        return (p ? free(p), -1 : -1);

    if (set)
        _strncat(pp, buffer + itr, var - itr);
    else
        _strncpy(pp, buffer + itr, var - itr + 1);

    set += var - itr;
    itr = var;
    p = pp;

    if (leng)
        *leng = set;

    *ptr = p;
    return (set);
}

/**
* handleSignal - a function which blocks copy shortcut
* @signalNum: number
* Return: void
*/

void handleSignal(__attribute__((unused))int signalNum)
{
    _puts("\n");
    _puts("$ ");
    _putchar(FLUSH_BUFFER);
}