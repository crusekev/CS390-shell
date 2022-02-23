/* 
    Kevin Cruse
    CS 390-01
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#define MAX_ARGS 50

int main()
{
    char *p;
    char input[1024];
    int i, j, k, l = 0, m;
    int my_argc;
    char *my_argv[MAX_ARGS];
    FILE *inFile, *outFile;
    char filetext;
    char buff[80];
    char *PS1 = "$";

    while(1)
    {
        printf("%s ", PS1);
        fgets(input, 1024, stdin); /* Get user input */
        p = strtok(input, " \t \n"); /* Tokenize user input */
        for(i = 0; p != 0; ++i)
        {
            if(i < (MAX_ARGS - 1))
            {
                my_argv[i] = p;
                p = strtok(0, " \t \n"); /* input is modified here */
            }
        }
        my_argv[i++] = 0;
        my_argc = i;

        /* Checking input for specified commands */
        int echo = strncmp(my_argv[0], "echo", 4);
        /* int echoN = strncmp(my_argv[1], "-n", 2); echo -n implementation causes seg faults, so I'm giving up on it */
        int list = strncmp(my_argv[0], "ls", 2);
        int promptChar = strncmp(my_argv[0], "PS1=", 4);
        int displayFile = strncmp(my_argv[0], "cat", 3);
        int copy = strncmp(my_argv[0], "cp", 2);
        int removeFile = strncmp(my_argv[0], "rm", 2);
        int makeDir = strncmp(my_argv[0], "mkdir", 5);
        int removeDir = strncmp(my_argv[0], "rmdir", 5);
        int exit = strncmp(my_argv[0], "exit", 4);
        
        if(echo == 0)
        {
            for(j = 0; j <= my_argc - 3; ++j)
            {
                printf("%s ", my_argv[j + 1]);
            }
            printf("\n");
        }
        /* else if(echoN == 0)
        {
            for(k = 0; k <= my_argc - 4; ++k)
            {
                printf("%s ", my_argv[k + 2]);
            }
            printf("\r");
        } */
        /* Added ls for debugging purposes */
        else if(list == 0)
        {
            system("ls");
        }
        else if(displayFile == 0)
        {
            if(my_argc > 3)
            {
                printf("Usage: Enter the cat command and one arg.\n");
                printf("The arg will be a file name to display.\n");
            }
            else if(my_argc == 3)
            {
                l = open(my_argv[1], O_RDONLY);
                while((m = read(l, buff, 80)) > 0)
                {
                    write(1, buff, m);
                }
                printf("\n");
                if(l == -1)
                {
                    printf("Usage: cat: %s: No such file or directory\n", my_argv[1]);
                }
                
            }
        }
        else if(copy == 0)
        {
            inFile = fopen(my_argv[1], "r");
            outFile = fopen(my_argv[2], "w");
            if(!inFile || !outFile || my_argc != 4)
            {
                printf("Usage: Enter the cp command and two args.\n");
                printf("First arg is the file to copy from. Second arg is file to copy to.\n");
            }
            while((filetext = fgetc(inFile)) != EOF)
            {
                fputc(filetext, outFile);
            }
            fclose(inFile);
            fclose(outFile);
        }
        else if(promptChar == 0)
        {
            printf("To use the PS1 command, please type PS1= arg, where arg is your desired prompt.\n");
            for(j = 0; j <= my_argc - 3; ++j)
            {
                PS1 = my_argv[j + 1];
            }
        }
        else if(removeDir == 0)
        {
            for(j = 0; j <= my_argc - 3; ++j)
            {
                if((rmdir(my_argv[j + 1])) == -1)
                {
                    printf("rmdir: failed to remove '%s': No such file or directory\n", my_argv[j + 1]);
                }
                else
                {
                    rmdir(my_argv[j + 1]);
                }
            }
        }
        else if(removeFile == 0)
        {
            for(j = 0; j <= my_argc - 3; ++j)
            {
                if((unlink(my_argv[j + 1])) == -1)
                {
                    printf("rm: cannot remove '%s': No such file or directory\n", my_argv[j + 1]);
                }
                else
                {
                    unlink(my_argv[j + 1]);
                }
            }
        }
        else if(makeDir == 0)
        {
            for(j = 0; j <= my_argc - 3; ++j)
            {
                if((mkdir(my_argv[j + 1], S_IRUSR | S_IWUSR | S_IXUSR)) == -1)
                {
                    printf("mkdir: cannot create directory ‘%s’: File exists\n", my_argv[j + 1]);
                }
                else
                {
                    mkdir(my_argv[j + 1], S_IRUSR | S_IWUSR | S_IXUSR);
                }
            }
        }
        else if(exit == 0)
        {
            return 0;
        }
    }
}