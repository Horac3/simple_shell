#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * exit_shell_prompt - determines length of linked list
 * @status: shell status
 *
 */

void exit_shell_prompt(int status)
{
	exit(status);
}

/**
 * parse_input_prompt - gets user input
 * @input: user input parameters
 * Return: returns the args.
 */


char **parse_input_prompt(char *input)
{
	char *arg = strtok(input, " \t\n");
	int i = 0;

	char **args = (char **)malloc(MAX_ARGS * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	arg = strtok(input, " \t\n");
	i = 0;
	while (arg != NULL && i < MAX_ARGS - 1)
	{
		args[i] = arg;
		arg = strtok(NULL, " \t\n");
		i++;
	}
	args[i] = NULL;
	return (args);
}

/**
 *read_input_prompt - reads user input
 *
 * Return: returns the input.
 */

char *read_input_prompt()
{
	char *input = (char *)malloc(MAX_INPUT_SIZE);

	if (input == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}
	printf("$ ");
	fgets(input, MAX_INPUT_SIZE, stdin);
	return (input);
}
