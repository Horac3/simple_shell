#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024
#define PROMPT "$ "

/**
 * read_shell_input - reads users input
 * @void: takes no parameters
 * Return: returns the input as a prompt.
 */

char *read_shell_input(void)
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
 * execute_shell_command - excutes user command
 * @command: command parameter
 * Return: returns void.
 */

void execute_shell_command(char *command)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork() failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        char *args[2];
        args[0] = command;
        args[1] = NULL;

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


