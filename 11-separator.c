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
 * process_commands - Process multiple commands
 * @commands: The commands to be processed
 */

void process_commands(char *commands)
{
	char *token;
	char *delimiter = ";";

	token = strtok(commands, delimiter);
	while (token != NULL)
	{
		execute_command(token);
		token = strtok(NULL, delimiter);
	}
}

/**
 * main - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS if success, EXIT_FAILURE if fail
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

		process_commands(command);
	}

	return EXIT_SUCCESS;
}
