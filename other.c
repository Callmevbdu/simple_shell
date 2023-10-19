#include "shell.h"

/**
 * isInter - function that checks if interactive mode is on
 * @getInfo: struct adress
 * Return: 1 if on, 0 otherwise.
*/

int isInter(info_t *getInfo)
{
    return (isatty(STDIN_FILENO) && getInfo->readFileDescriptor <= 2);
}

/**
 * isDelimeter - function that checks if @ch is a delimeter
 * @ch: character to be checked
 * @del: delimiter
 * Return: 1 success, 0 otherwise.
*/

int isDelimeter(char ch, char *del)
{
    while (*del)
        if (*del++ == ch)
            return (1);
    
    return (0);
}

/**
 * _isAlpha - a function that checks if @ch is a letter, lowercase or upper
 * @ch: input char
 * Return: 1 success, 0 otherwise.
*/

int _isAlpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
    else
	    return (0);
}

/**
 * _atoi - converts a string to an integer
 * @str: string to be converted
 * Return: the int converted from the string
 */

int _atoi(char *str)
{
	int len, sgn, flg, ret;
    unsigned int sum = 0;

	sgn = 1;
	flg = 0;

	for (len = 0; str[len] != '\0' && flg != 2; len++)
	{
		if (str[len] == '-')
			sgn *= -1;

		if (str[len] >= '0' && str[len] <= '9')
		{
            flg = 1;
            sum *= 10;
            sum += (str[len] - '0');
        }
        else if (flg == 1)
            flg = 2;
	}

	if (sgn == -1)
    {
		ret = -sum;
    }
    else
    {
        ret = sum;
    }
	return (ret);
}

/**
 * _atoiError - converts a string to an integer
 * @str: string to be converted
 * Return: converted num (success), -1 otherwise.
 */

int _atoiError(char *str)
{
	int len = 0;
    unsigned long int sum = 0;

    if (*str == '+')
    {
        str++;
    }
    
	for (len = 0; str[len] != '\0'; len++)
	{
		if (str[len] >= '0' && str[len] <= '9')
		{
            sum *= 10;
            sum += (str[len] - '0');
            
            if (sum > INT_MAX)
            {
                return (-1);
            }
        }
        else
            return (-1);
    }

	return (sum);
}