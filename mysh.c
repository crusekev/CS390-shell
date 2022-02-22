#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#define MAX_ARGS 50

int main()
{
    char *p;
    char input[1024];
    int i;
    int j;
    int k;
    int my_argc;
    char *my_argv[MAX_ARGS];
    FILE *inFile, *outFile;
    char filetext;

    while(1)
    {
        fgets(input, 1024, stdin); /* Get user input */
        /* Tokenize user input */
        p = strtok(input, " \t \n");
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
        int echoN = strncmp(my_argv[0], "echo -n", 7);
        int list = strncmp(my_argv[0], "ls", 2);
        int promptChar = strncmp(my_argv[0], "PS1", 3);
        int copy = strncmp(my_argv[0], "cp", 2);
        int removeFile = strncmp(my_argv[0], "rm", 2);
        int makeDir = strncmp(my_argv[0], "mkdir", 5);
        int removeDir = strncmp(my_argv[0], "rmdir", 5);
        int exit = strncmp(my_argv[0], "exit", 4);
        
        if(echo == 0)
        {
            for(j = 0; j < strlen(*my_argv) - 2; ++j)
            {
                printf("%s ", my_argv[j + 1]);
            }
            printf("\n");
        }
        if(echoN == 0)
        {
            for(k = 0; k < strlen(*my_argv) - 2; ++k)
            {
                printf("%s ", my_argv[k + 2]);
            }
            printf("\r");
        }
        else if(list == 0)
        {
            system("ls");
        }
        else if(copy == 0)
        {
            inFile = fopen(my_argv[1], "r");
            outFile = fopen(my_argv[2], "w");
            if(!inFile || !outFile || my_argc != 4)
            {
                printf("Usage: Please enter the cp command and two args.\n");
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
            /* system("PS1='my_argv[1]' bash"); */
        }
        else if(removeFile == 0)
        {
            unlink(my_argv[1]);
        }
        else if(removeDir == 0)
        {
            rmdir(my_argv[1]);
        }
        else if(makeDir == 0)
        {
            mkdir(my_argv[1], S_IRUSR | S_IWUSR | S_IXUSR);
        }
        else if(exit == 0)
        {
            return 0;
        }
    }
}