#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/**
 * execute_command - executes user command
 * @args: command line arguments as parameters
 * @envp: path
 * Return: returns the input as a prompt.
 */
void execute_command(char **args, char **envp)
{
	char *path = getenv("PATH"), *full_path = NULL, *dir = strtok(path, ":");

	while (dir != NULL)
	{
		full_path = (char *)malloc(strlen(dir) + strlen(args[0]) + 2);
		if (full_path == NULL)
		{
			perror("malloc() failed");
			exit(EXIT_FAILURE);
		}
		sprintf(full_path, "%s/%s", dir, args[0]);
		if (access(full_path, F_OK) == 0)
		{
			break;
		}
		free(full_path);
		dir = strtok(NULL, ":");
	}
	if (dir == NULL)
	{
		printf("%s: command not found\n", args[0]);
		return;
	}
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork() failed");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(full_path, args, envp) == -1)
		{
			perror("execve() failed");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid() failed");
		exit(EXIT_FAILURE);
	}
	free(full_path);
}

/**
 * main - main function
 * @argc: command line arguments as parameters
 * @argv: command line arguments as parameters
 * @envp: path
 * Return: returns 0.
 */
int main(int argc, char **argv, char **envp)
{
	while (1)
	{
		char **args = read_input();

		if (args[0] != NULL)
		{
			execute_command(args, envp);
		}
		free(args);
	}
	return (0);
}

