#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT "$ "
#define MAX_ARGS 64


char *read_shell_input(void);
execute_shell_command(char *command);

execute_command(char **args);
char **read_input(void);

char **read_path_input(void);
void execute_path_command(char **args);

custom_getline(void);

void exit_shell();
char **parse_shell_input(char *input);
char *read_input_shell();

void exit_shell_prompt(int status);
char **parse_input_prompt(char *input);
char *read_input_prompt();

char **parse_input_status(char *input);
void exit_shell_status(int status);
char *read_input_status();
int execute_builtin(char **args);

populate_env_list(info);
read_history(info);
hsh(info, argv);



#endif
