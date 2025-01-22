#ifndef AUTOGIT_H
#define AUTOGIT_H
#pragma once

int run_git_command(char* GIT_COMMAND, char** GIT_COMMAND_ARGUMENTS); // for process control

void help();  // display command information

int init(char* REMOTE_URL); // remote functions
int forget();
int info();

int new(char* TARGET_NAME); // branch functions
int change(char* TARGET_NAME);
int delete(char* TARGET_NAME);

int push(char* BRANCH_NAME); // repo change functions
int push_commit(char* BRANCH_NAME, char* COMMIT_MESSAGE);
int pull(char* BRANCH_NAME);

int kill(); // for removing local

#endif