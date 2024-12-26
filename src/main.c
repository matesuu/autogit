#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "AUTOGIT.h"

int main(int argc, char** argv)
{
    char* help_str = "help";
    char* init_str = "init";
    char* remove_str = "remove";
    char* info_str = "info";
    char* new_str = "new";
    char* switch_str = "switch";
    char* delete_str = "delete";
    char* push_str = "push";
    char* pull_str = "pull";

    if(argc < 2)
    {
        help();
        return 0;
    }

    if(strcmp(help_str, argv[1]) == 0)
    {
        help();
        return 0;
    }

    else if(strcmp(init_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: remote repository url ");

            return 1;
        }

        else
        {
            init(argv[2]);
            printf("process finished ");

            return 0;
        }
    }

    else if(strcmp(remove_str, argv[1]) == 0)
    {
        forget();
        printf("process finished ");

        return 0;
    }

    else if(strcmp(info_str, argv[1]) == 0)
    {
        info();
        printf("process finished ");

        return 0;
    }

    else if(strcmp(new_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: target branch name ");
            
            return 1;
        }

        new(argv[2]);
        printf("process finished ");

        return 0;
    }

    else if(strcmp(switch_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: target branch name ");

            return 1;
        }

        change(argv[2]);
        printf("process finished ");

        return 0;
    }

    else if(strcmp(delete_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: target branch name ");

            return 1;
        }

        delete(argv[2]);
        printf("process finished ");

        return 0;
    }

    else if(strcmp(push_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: branch name ");

            return 1;
        }

        push(argv[2]);
        printf("process finished ");

        return 0;
    }

    else if(strcmp(pull_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: branch name ");

            return 1;
        }

        pull(argv[2]);
        printf("process finished ");

        return 0;
    }

    else
    {
        perror("error: unknown command ");

        return 1;
    }

    return 0;   
}