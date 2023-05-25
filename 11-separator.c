#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "shell.h"

/**
 * execute_separator_command - Execute a single command
 * @command: The command to be executed
 *
 * Description: This function executes a single command by forking a child
 * process and calling execvp.
 */
void execute_separator_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		char *args[] = {"/bin/sh", "-c", NULL, NULL};
		args[2] = command;

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
 *
 * Description: This function processes multiple commands separated by semicolons.
 * It splits the input into individual commands and executes them using
 * execute_separator_command.
 */
void process_commands(char *commands)
{
	char *token;
	char *delimiter = ";";

	token = strtok(commands, delimiter);
	while (token != NULL)
	{
		execute_separator_command(token);
		token = strtok(NULL, delimiter);
	}
}

/**
 * main - Entry point of the program
 * @argc: The argument count
 * @argv: The argument vector
 *
 * Description: This function is the entry point of the program.
 * It prompts the user for commands, processes them using process_commands,
 * and repeats until the user exits.
 *
 * Return: Always returns EXIT_SUCCESS.
 */
int main(int argc, char **argv)
{
	char command[256];
	if (argc > 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		return EXIT_FAILURE;
	}

	while (1)
	{
		printf("$ ");

		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		process_commands(command);
	}

	return EXIT_SUCCESS;
}
