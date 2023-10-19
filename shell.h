#ifndef SHELL_H_
#define SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


/* CHAINING COMMANDS */
#define IS_NORMAL 0
#define IS_OR 1
#define IS_AND 2
#define IS_CHAIN 3

/* BUFFERS */
#define READ_BUFFER 1024
#define WRITE_BUFFER 1024
#define FLUSH_BUFFER -1

/* CONVERT NUM */
#define LOWCASE 1
#define UNSIGNED 2

/* GET_LINE FUNCTION */
#define USE_GETLINE 0
#define USE_STRTOK 0

/* HISTORY */
#define HISTORY_FILE ".shell_history"
#define HISTORY_MAX 4096

extern char **environ;

/**
 * struct stingsList - a parameters linked list for related function
 * @number: numbers parameter
 * @strings: strings parameter
 * @complete: continue to next node
*/

typedef struct stingsList
{
    int number;
    char *strings;
    struct stingsList *complete;
} list_t;

/**
 * struct informations - a struct that passes main informations.
 * @history: history parameter
 * @alias: alias parameter
 * @environmentL: local copy of environment
 * @environmentC: custom modified copy of environment
 * @environmentChanged: whether environment is changed 
 * @directory: path of current command
 * @arguments: argument string
 * @argumentc: argument count
 * @argumentv: argument vector
 * @lineCount: line count parameter
 * @lineCountF: line count flag
 * @errorNumber: system error code
 * @status: status of last command
 * @fileName: filename parameter
 * @commandBuffer: checks if chaining happend
 * @commandBufferType: whether 'AND' or 'OR' or ';'
 * @readFileDescriptor: file descriptor parameter
 * @historyCount: history lines counter.
*/

typedef struct informations
{
    list_t *history;
    list_t *alias;
    list_t *environmentL;
    char **environmentC;
    int environmentChanged;
    char *directory;
    char *arguments;
    char **argumentv;
    int argumentc;
    unsigned int lineCount;
    int lineCountF;
    int errorNumber;
    int status;
    char *fileName;
    char **commandBuffer;
    int commandBufferType;
    int readFileDescriptor;
    int historyCount;
} info_t;

#define INFO_INIT {NULL, NULL, NULL, NULL, 0, NULL, NULL, NULL, 0, 0, 0, 0, 0, NULL, NULL, 0, 0, 0}

/**
 * struct parameters - a parameters linked list for related function
 * @command: command parameter
 * @task: function parameter
*/

typedef struct parameters
{
    char *command;
    int (*task)(info_t *);
} parameters_t;


/* STRINGS */
char *strstr(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtwo(char *, char);
void _puts(char *);
void _eputs(char *);
int _putchar(char);
int _eputchar(char);
int _strlen(char *);
int _strcmp(char *, char *);
int _putsfDesc(char *s, int fDesc);
int _putfDesc(char c, int fDesc);

/* LISTS */
list_t *addNode(list_t **, const char *, int);
list_t *addNodeEnd(list_t **, const char *, int);
int removeNode(list_t **, unsigned int);
list_t *listPrefix(list_t *, char *, char);
size_t listPrint(const list_t *);

size_t listLength(const list_t *);
void listFree(list_t **);
char **listString(list_t *);
size_t stringPrint(const list_t *);
ssize_t getIndex(list_t *, list_t *);


/* ENVIRONMENT */
int _curEnv(info_t *);
char *_getEnv(info_t *, const char *);
int _initEnv(info_t *);
int _remEnv(info_t *);
int popEnv(info_t *);

char **getEnv2(info_t *);
int _setEnv(info_t *, char *, char *);
int _unsetEnv(info_t *, char *);


/* EMULATOR */
int _emuExit(info_t *);
int _emuCD(info_t *);
int _emuHelp(info_t *);
int _emuHistory(info_t *);
int _emuAlias(info_t *);
int emuSetAlias(info_t *, char *);
int emuUnAlias(info_t *, char *);
int emuPrintAlias(list_t *);

/* HISTORY */
char *getHis(info_t *info);
int writeHis(info_t *info);
int readHis(info_t * info);
int buildHis(info_t *info, char *buffer, int count);
int numberHis(info_t *info);

/* CHAINING*/
void checkChain (info_t *, char *, size_t *, size_t, size_t);
int isChain(info_t *, char *, size_t *);
int replaceString (char **, char *);
int replaceVar(info_t *);
int replaceAlias (info_t *);

/* BUFFER FUNCTIONS*/
ssize_t inputBuffer(info_t *, char **, size_t *);
ssize_t readBuffer(info_t *, char *, size_t *);
ssize_t getInput(info_t *);
int _getLine(info_t *, char **, size_t *);
void handleSignal(int);

/* MAIN LOOP */
int shellLoop(info_t *, char **);
int BuiltInCMD(info_t *);
void findCMD(info_t *);
void forkCMD(info_t *);

/* MEMORY */
void memFree(char **);
void *_memAlloc(void *, unsigned int, unsigned int);
char *_memSet(char *, char, unsigned int);
int ptrFree(void **);

/* SYSTEM */
int isExe(info_t *, char *);
char *charDuplicate(char *, int, int);
char *findPath(info_t *, char *, char *);

/* INFOS */
void infoClear(info_t *);
void infoFree(info_t *, int);
void infoSet(info_t *, char **);

/* OTHER */
int isInter(info_t *);
int isDelimeter(char, char *);
int _isAlpha(int);
int _atoi(char *);
int _atoiError(char *);
void printError(info_t *, char *);
int printDecimal(int, int);
char *convertNum(long int, int, int);
void unComment(char *);

#endif