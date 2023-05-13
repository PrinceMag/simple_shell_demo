#include "shell.h"

void cmdPrompt(char **argVector, char **envVal)
{
    char *lineString = NULL;
    int lineStringIndex,status;
    ssize_t numChar;
    size_t n = 0;
    char *argVal[] = {NULL, NULL};
    pid_t childProcessID;

    while(true)
    {
        if (isatty(STDIN_FILENO))
        {
            printf("cisfun$ ");
        }

        numChar = getline(&lineString, &n, stdin);
        if(numChar == -1)
        {
            free(lineString);
            exit(EXIT_FAILURE);
        }
        lineStringIndex = 0;
        while(lineString[lineStringIndex] != '\0')
        {
            if(lineString[lineStringIndex] == '\n')
            {
                lineString[lineStringIndex] = 0;
            }
            lineStringIndex++;
        }
        argVal[0] = lineString;
        childProcessID = fork();
        if(childProcessID == -1)
        {
            free(lineString);
            exit(EXIT_FAILURE);
        }
        if (childProcessID == 0)
        {
            if (execve(argVal[0], argVal, envVal) -1)
            {
                printf("%s: No such file or directory\n", argVector[0]);
            }
        }else{
            wait(&status);
        }

    }
}