#ifndef AUTOGIT_H
#define AUTOGIT_H

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS);
int init(char* REMOTE_URL);
int push();
int pull();

#endif