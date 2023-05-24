#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT "$ "

char **read_path_input(void);
void execute_path_command(char **args);

/**
 * read_path_input - determines length of linked list
 *
 * Return: returns args
 */


char **read_path_input(void)
{
	char *input = (char *)malloc(MAX_INPUT_SIZE);
	char **args;
	int i;
	char *token;


	input = (char *)malloc(MAX_INPUT_SIZE);
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

	args = (char **)malloc(MAX_INPUT_SIZE * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}

	i = 0;
	token = strtok(input, " \n");

	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \n");
	}
	args[i] = NULL;

	free(input);
	return (args);
}


/**
 * execute_path_input - determines length of linked list
 * @args: commandline arguments
 * 
 */

void execute_path_command(char **args)
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
