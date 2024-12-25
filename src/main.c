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
            init_msg();
            init(argv[2]);

            return 0;
        }
    }

    else if(strcmp(remove_str, argv[1]) == 0)
    {
        forget_msg();
        forget();

        return 0;
    }

    else if(strcmp(info_str, argv[1]) == 0)
    {
        info_msg();
        info();

        return 0;
    }

    else if(strcmp(push_str, argv[1]) == 0)
    {
        push_msg();
        push();

        return 0;
    }

    else if(strcmp(pull_str, argv[1]) == 0)
    {
        pull_msg();
        pull();

        return 0;
    }

    else
    {
        perror("error: unknown command ");

        return 1;
    }

    return 0;   
}