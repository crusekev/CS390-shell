#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define MAX_ARGS 50

int main()
{
    char *p;
    char input[1024];
    int i;
    int j;
    int my_argc;
    char *my_argv[MAX_ARGS];

    while(1)
    {
        fgets(input, 1024, stdin); /* Get user input */
        /* Tokenize user input */
        p = strtok(input, " \t");
        for(i = 0; p != 0; ++i)
        {
            if(i < (MAX_ARGS - 1))
            {
                my_argv[i] = p;
                p = strtok(0, " \t"); /* input is modified here */
            }
        }
        my_argv[i++] = 0;
        my_argc = i;

        /* Checking input for specified commands */
        int echo = strncmp(my_argv[0], "echo", 4);
        int ls = strncmp(my_argv[0], "ls", 2);
        int promptChar = strncmp(my_argv[0], "PS1", 3);
        int exit = strncmp(my_argv[0], "exit", 4);
        int endl = strncmp(*my_argv, "\n", 1024);
        char *token;
        
        if(echo == 0)
        {
            /* Printing the echo input causes a seg fault */
            for(j = 0; *my_argv != "\n"; ++j)
            {
                printf("%s ", my_argv[j + 1]);
            }
            /* else if(strncmp(my_argv[1] == "-n", 7))
            {
                printf("%s", my_argv[j + 1])
            } */
        }
        else if(ls == 0)
        {
            system("ls");
        }
        else if(promptChar == 0)
        {
            system("PS1='my_argv[1]' bash");
        }
        else if(exit == 0)
        {
            return 0;
        }
    }
}