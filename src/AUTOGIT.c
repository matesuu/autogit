/*

Note: For the sake of simplicity, the name of a remote repository when initialized will always be 'origin'. As this is a tool
aimed to simplify the use of git as a tool, there are no current plans to change this design facet. Therefore, autogit only supports
the use of a singular remote. Will work on this later...

p.s. nettspend sucks

- matesuu

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
    printf("init - initialize a local and remote repository and create branch main - autogit init <remote_url_name> \n");
    printf("deinit - remove currently existing remote - autogit deinit \n");
    printf("info - display current information of current remotes and branches - autogit info \n");
    printf("new - creates a new branch within remote - autogit new <branch_name> \n");
    printf("switch - changes current working branch - autogit change <branch_name> \n");
    printf("delete - deletes a given branch from remote - autogit delete <branch_name> \n");
    printf("push - push all current changes to a specified branch - autogit push <branch_name> <optional: commit message> \n");
    printf("pull - pull all current changes from a specified branch - autogit pull <branch_name> \n");
    printf("kill - removes remote repository and delete the .git folder of a directory (!USE WITH CAUTION!) - autogit kill \n\n");

    printf("written by matesuu (December 2024) \n\n");
}

int init(char* REMOTE_URL)
{
    char* args_0[] = {"git", "init", NULL};
    run_git_command("git", args_0);

    char* args_1[] = {"git", "init", "&&", "git", "symbolic-ref", "HEAD", "refs/heads/main", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "config", "--global", "init.defaultBranch", "main", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "remote", "add", "origin", REMOTE_URL, NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "remote", "-v", NULL};
    run_git_command("git", args_4);

    printf("successfully initialized and added remote repository ");

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

    char* args_2[] = {"git", "branch", NULL};
    run_git_command("git", args_2);

    return 0;
}

int new(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "checkout", "-b", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int change(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "checkout", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int delete(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "branch", "-d", BRANCH_NAME, NULL};
    run_git_command("git", args_1);

    return 0;
}

int push(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "add", ".", "--all", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "commit", "-m", "commited to repo using autogit", NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "pull", "--rebase", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_4);

    char* args_5[] = {"git", "push", "-u", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_5);

    return 0;
}

int push_commit(char* BRANCH_NAME, char* COMMIT_MESSAGE)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "add", ".", "--all", NULL};
    run_git_command("git", args_2);

    char* args_3[] = {"git", "commit", "-m", COMMIT_MESSAGE, NULL};
    run_git_command("git", args_3);

    char* args_4[] = {"git", "pull", "--rebase", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_4);

    char* args_5[] = {"git", "push", "-u", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_5);

    return 0;
}

int pull(char* BRANCH_NAME)
{
    char* args_1[] = {"git", "status", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"git", "pull", "origin", BRANCH_NAME, NULL};
    run_git_command("git", args_2);

    return 0;
}

int kill()
{
    char flag = '\0';

    char* args_1[] = {"git", "remote", "remove", "origin", NULL};
    run_git_command("git", args_1);

    char* args_2[] = {"rm", "-rf", ".git", NULL};
    run_git_command("rm", args_2);

    return 0;
}