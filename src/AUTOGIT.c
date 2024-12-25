/*

Note: For the sake of simplicity, the name of a remote repository when initialized will always be 'origin'. As this is a tool
aimed to simplify the use of git as a tool, there are no current plans to change this design facet.

*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS)
{
    pid_t PARENT_ID = fork();

    if(PARENT_ID < 0)
    {
        perror("error: could not create child process");
        
        exit(1);
    }


    if(PARENT_ID == 0)
    {
        execvp(GIT_COMMAND, GIT_COMMAND_ARGUMENTS);

        perror("error: could not execute child process");
        
        exit(1);
    }

    else
    {
        int status = 0;
        waitpid(PARENT_ID, &status, 0);

        if(!WIFEXITED(status))
        {
            exit(1);
        }
    }

    return 0;
}

void help()
{
    printf("\n\nhelp - \n\n");
    printf("init - initialize a local and remote repository - autogit init <remote_url_name> \n");
    printf("remove - remove currently existing remote - autogit remove \n");
    printf("info - display current information of current remotes - autogit info \n");
    printf("push - push all current changes in local to remote - autogit push \n");
    printf("pull - pull all current changes from remote to local - autogit pull \n\n");
}

int init(char* REMOTE_URL)
{
    char* args_1[] = {"git", "init", "&&", "git", "symbolic-ref", "HEAD", "refs/heads/main", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "config", "--global", "init.defaultBranch", "main", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "remote", "add", "origin", REMOTE_URL, NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "remote", "-v", NULL};
    run_git_command("git", args_4);

    return 0;
}

int forget()
{
    char* args_1[] = {"git", "remote", "remove", "origin", NULL};
    run_git_command("git", args_1);

    return 0;
}

int info()
{
    char* args_1[] = {"git", "remote", "-v", NULL};
    run_git_command("git", args_1);

    return 0;
}

int push()
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "add", ".", "--all", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "commit", "-m", "commited to repo using autogit", NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "pull", "--rebase", "origin", "main", NULL};
    run_git_command("git", args_4);

    char* args_5[] = {"git", "push", "-u", "origin", "main", NULL};
    run_git_command("git", args_5);

    return 0;
}

int pull()
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "pull", "origin", "main", NULL};
    run_git_command("git", args_2);

    return 0;
}
