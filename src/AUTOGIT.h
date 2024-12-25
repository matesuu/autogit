#ifndef AUTOGIT_H
#define AUTOGIT_H

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS); // for process control

int init(char* REMOTE_URL); // remote functions
int forget();
int info();

int push(); // repo change functions
int pull();

#endif