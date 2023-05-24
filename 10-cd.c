#include "shell.h"

/**
 * execute_command - Execute a single command
 * @command: The command to be executed
 */

void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char *args[] = {"/bin/sh", "-c", command, NULL};
		execvp(args[0], args);
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * change_directory - Change the current directory
 * @path: The path to change the directory to
 */

void change_directory(char *path)
{
	char cwd[256];

	if (path == NULL || strcmp(path, "") == 0)
	{
		path = getenv("HOME");
	}

	if (strcmp(path, "-") == 0)
	{
		path = getenv("OLDPWD");
		printf("%s\n", path);
	}

	if (chdir(path) != 0)
	{
		perror("Error");
		return;
	}

	getcwd(cwd, sizeof(cwd));
	setenv("PWD", cwd, 1);
}

/**
 * main - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if fail
 */

int main(int argc, char **argv)
{
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}

	char command[256];
	while (1)
	{
		printf("$ ");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		if (strncmp(command, "cd", 2) == 0)
		{
			char *arg = strtok(command, " ");
			arg = strtok(NULL, " ");
			change_directory(arg);
		}
		else
		{
			execute_command(command);
		}
	}

	return EXIT_SUCCESS;
}
