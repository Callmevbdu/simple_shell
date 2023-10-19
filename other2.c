#include "shell.h"

/**
 * printError - function that prints an error
 * @getInfo: parameter info struct
 * @etype: string error type
 * Return: error message
 */

void printError(info_t *getInfo, char *etype)
{
    _eputs(getInfo->fileName);
    _eputs(": ");
    printDecimal(getInfo->lineCount, STDERR_FILENO);
    _eputs(": ");
    _eputs(getInfo->argumentv[0]);
    _eputs(": ");
    _eputs(etype);
}

/**
 * printDecimal - function that prints a decimal number base 10
 * @num: input
 * @fDesc: file descriptor
 * Return: number of chars printed
 */

int printDecimal(int num, int fDesc)
{
    int (*__putchar)(char) = _putchar;
    unsigned int var, dec;
    int itr, sum = 0;

    if (fDesc == STDERR_FILENO)
        __putchar = _eputchar;

    if (num < 0)
    {
        var = -num;
        __putchar('-');
        sum++;
    }
    else
        var = num;

    dec = var;

    for (itr = 1000000000; itr > 1; itr /= 10)
    {
        if (var / itr)
        {
            __putchar('0' + dec / itr);
            sum++;
        }

        dec %= itr;
    }

    __putchar('0' + dec);
    sum++;

    return (sum);
}

/**
 * convertNum - function that convert numbers between bases
 * @n: number
 * @b: base
 * @f: flag
 * Return: output string
 */

char *convertNum(long int n, int b, int f)
{
    static char *arr;
    static char buff[50];
    char sgn = 0;
    char *p;
    unsigned long nn = n;

    if (!(f & UNSIGNED) && n < 0)
    {
        nn = -n;
        sgn = '-';
    }

    arr = f & LOWCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    p = &buff[49];
    *p = '\0';

    do
    {
        *--p = arr[nn % b];
        nn /= b;
    } while (nn != 0);

    if (sgn)
        *--p = sgn;
    return (p);
}

/**
 * unComment - function that removes comments from a text
 * @buffer: string input
 * Return: 0 always.
 */

void unComment(char *buffer)
{
    int itr;

    for (itr = 0; buffer[itr] != '\0'; itr++)
        if (buffer[itr] == '#' && (!itr || buffer[itr - 1] == ' '))
        {
            buffer[itr] = '\0';
            break;
        }
}