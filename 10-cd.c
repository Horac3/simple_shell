#include "shell.h"

/**
 * execute_cd_command_10 - Execute a single command
 * @command: The command to be executed
 */

void execute_cd_command_10(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char **args = malloc(4 * sizeof(char *));
		args[0] = "/bin/sh";
		args[1] = "-c";
		args[2] = command;
		args[3] = NULL;
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
 * change_directory_10 - Change the current directory
 * @path: The path to change the directory to
 */

void change_directory_10(char *path)
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
 * cd_10 - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if fail
 */

int cd_10(int argc, char **argv)
{
	char commands[256];
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}

	
	while (1)
	{
		printf("$ ");
		fgets(commands, sizeof(commands), stdin);
		commands[strcspn(commands, "\n")] = '\0';

		if (strncmp(commands, "cd", 2) == 0)
		{
			char *arg = strtok(commands, " ");
			arg = strtok(NULL, " ");
			change_directory(arg);
		}
		else
		{
			execute_cd_command_10(commands);
		}
	}

	return EXIT_SUCCESS;
}
