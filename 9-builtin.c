#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64

/**
 * exit_shell_status - current shell status function
 * @status: current shell status
 */

void exit_shell_status(int status)
{
	exit(status);
}

/**
 * parse_input_status - gets user input
 * @input: user input parameters
 * Return: returns the args.
 */

char **parse_input_status(char *input)
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
 * read_input_status - gets user input
 * Return: returns the args.
 */

char *read_input_status()
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

/**
 * execute_builtin - executes the setenv and unsetenv
 * @args: commandline arguments
 * Return: returns 0.
 */

int execute_builtin(char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
		if (args[1] != NULL)
		{
			int status = atoi(args[1]);
			exit_shell_status(status);
		}
		else
		{
			printf("Usage: exit status\n");
		}
		return (1);
	}
	else if (strcmp(args[0], "setenv") == 0)
	{
		if (args[1] != NULL && args[2] != NULL)
		{
			if (setenv(args[1], args[2], 1) != 0)
			{
				fprintf(stderr, "Failed to set variable\n");
			}
		}
		else
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		}
		return (1);
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] != NULL)
		{
			if (unsetenv(args[1]) != 0)
			{
				fprintf(stderr, "Failed to unset variable\n");
			}
		}
		else
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		}
		return (1);
	}
	return (0);
}

