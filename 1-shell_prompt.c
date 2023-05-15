#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT "$ "

/**
 * read_input - reads users input
 * @void: takes no parameters
 * Return: returns the input as a prompt.
 */

char *read_input(void)
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
	return (input);
}

/**
 * execute_command - excutes user command
 * @command: command parameter
 * Return: returns void.
 */

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork() failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		char *args[] = {command, NULL};

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
 * main - main file
 * @void: takes no parameters
 * Return: returns 0.
 */

int main(void)
{
	while (1)
	{
		char *input = read_input();

		if (strlen(input) > 1)
		{
			input[strlen(input) - 1] = '\0';
			execute_command(input);
		}
		free(input);
	}
	return (0);
}

