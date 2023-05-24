#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * exit_shell - exits the shell
 */

void exit_shell(void)
{
	exit(EXIT_SUCCESS);
}

/**
 * parse_shell_input - gets user input
 * @input: user input parameters
 * Return: returns the args.
 */

char **parse_shell_input(char *input)
{
	char *arg;
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
 * read_input_shell - reads user input
 *
 * Return: returns the input.
 */

char *read_input_shell()
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


