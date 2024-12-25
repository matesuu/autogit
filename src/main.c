#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "AUTOGIT.h"

int main(int argc, char** argv)
{
    char* init_str = "init";
    char* push_str = "push";
    char* pull_str = "pull";

    if(argc < 2)
    {
        perror("error: missing positional arguments");
        return 1;
    }

    if(strcmp(init_str, argv[1]) == 0)
    {
        if(argc < 3)
        {
            perror("missing argument: remote repository url");

            return 1;
        }

        else
        {
            init(argv[2]);
            printf("successfully initialized remote repository");

            return 0;
        }
    }

    else if(strcmp(push_str, argv[1]) == 0)
    {
        push();
        printf("sucessfully pushed refs to remote repository");

        return 0;
    }

    else if(strcmp(pull_str, argv[1]) == 0)
    {
        pull();
        printf("sucessfully pulled refs from remote repository");

        return 0;
    }

    else
    {
        perror("error: unknown command");

        return 1;
    }

    return 0;   
}