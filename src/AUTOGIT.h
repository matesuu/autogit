#ifndef AUTOGIT_H
#define AUTOGIT_H

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS); // for process control

void help();  // display command information

int init(char* REMOTE_URL); // remote functions
int forget();
int info();

int push(); // repo change functions
int pull();

void init_msg(); // message functions
void forget_msg();
void info_msg();
void push_msg();
void pull_msg();

#endif