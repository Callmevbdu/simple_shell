#include "shell.h"

/**
 * main - main entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: success (0), 1 otherwise.
*/

int main(int argc, char **argv)
{
    info_t getInfo[] = { INFO_INIT };
    int fDesc = 2;

    asm ("mov %1, %0\n\t"
        "add $3, %0"
        : "=r" (fDesc)
        : "r" (fDesc));

    if (argc == 2)
    {
        fDesc = open(argv[1], O_RDONLY);

        if (fDesc == -1)
        {
            if (errno == EACCES)
                exit(126);

            if (errno == ENOENT)
            {
                _eputs(argv[0]);
                _eputs(": 0: Can't open ");
                _eputs(argv[1]);
                _eputchar('\n');
                _eputchar(FLUSH_BUFFER);
                exit(127);
            }

            return (EXIT_FAILURE);
        }

        getInfo->readFileDescriptor = fDesc;
    }

    popEnv(getInfo);
    readHis(getInfo);
    shellLoop(getInfo, argv);
    return (EXIT_SUCCESS);
}