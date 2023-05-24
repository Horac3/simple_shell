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
#define MAX_VARIABLE_LENGTH 100

/**
 * struct alias_s - Alias linked list structure
 * @name: Name of the alias
 * @value: Value of the alias
 * @next: Pointer to the next alias
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/**
 * struct variable_s - Environment variable linked list structure
 * @name: Name of the variable
 * @value: Value of the variable
 * @next: Pointer to the next variable
 */
typedef struct variable_s
{
	char *name;
	char *value;
	struct variable_s *next;
} variable_t;

/**
 * struct shell_s - Shell structure
 * @aliases: Pointer to the aliases linked list
 * @variables: Pointer to the variables linked list
 * @last_status: Last command exit status
 * @pid: Shell's process ID
 */
typedef struct shell_s
{
	alias_t *aliases;
	variable_t *variables;
	int last_status;
	pid_t pid;
} shell_t;

typedef struct {
	int readfd;
} info_t;

#define INFO_INIT { 0 }


char *read_shell_input(void);
void execute_shell_command(char *command);

void execute_command(char **args);
char **read_input(void);

char **read_path_input(void);
void execute_path_command(char **args);

char *custom_getline(void);

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
void print_environment(char **env);
void env_shell(char **env);
void exit_shell(void);
void execute_command(char *command);
void change_directory(char *path);
void process_commands(char *commands);
void process_command(char *command);
void process_file(char *filename);
void print_alias_list(alias_t *aliases);
void print_aliases(alias_t *aliases, char **names);
int alias_builtin(shell_t *state, char **args);
char *replace_variable(shell_t *state, char *command);
void remove_comments(char *command);

alias_t *create_alias(char *name, char *value);
variable_t *create_variable(char *name, char *value);
alias_t *find_alias(alias_t *aliases, char *name);
variable_t *find_variable(variable_t *variables, char *name);
void add_variable(variable_t **variables, variable_t *new_variable);
int add_alias(alias_t **aliases, alias_t *new_alias);
char *get_variable_value(variable_t *variables, char *name);
char *_itoa(int num);
void *_realloc(void *ptr, size_t size);

#endif
