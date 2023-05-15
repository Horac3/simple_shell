#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - executes user command
 * @args: command line arguments as parameters
 * Return: returns the input as a prompt.
 */
void execute_command(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork() failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp() failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid() failed");
		exit(EXIT_FAILURE);
	}
}

/**
 * read_input - reads user input
 * @void: takes no parameters
 * Return: returns commandline arguments.
 */
char **read_input(void)
{
	char *input = (char *)malloc(MAX_INPUT_SIZE);

	if (input == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	printf("%s", PROMPT);

	if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
	{
		free(input);
		if (errno == 0)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		perror("fgets() failed");
		exit(EXIT_FAILURE);
	}
	char **args = (char **)malloc(MAX_INPUT_SIZE * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	int i = 0;

	char *token = strtok(input, " \n");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;
	return (args);
}

/**
 * main - main to excute functions
 * @void: takes no parameters
 * Return: returns 0.
 */
int main(void)
{
	while (1)
	{
		char **args = read_input();

		if (args[0] != NULL)
		{
			execute_command(args);
		}
		free(args);
	}
	return (0);
}

