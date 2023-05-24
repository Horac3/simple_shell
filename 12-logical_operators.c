#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * main - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if fail
 */

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		process_file(argv[1]);
		return EXIT_SUCCESS;
	}
	else if (argc > 2)
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		return EXIT_FAILURE;
	}

	char command[256];
	char *token;
	char *delimiter = "&&";
	while (1)
	{
		printf("$ ");
		fgets(command, sizeof(command), stdin);
		command[strcspn(command, "\n")] = '\0';

		token = strtok(command, delimiter);
		while (token != NULL)
		{
			process_command(token);
			token = strtok(NULL, delimiter);
		}
	}

	return EXIT_SUCCESS;
}

/**
 * process_command - Process a single command
 * @command: The command to be processed
 */

void process_command(char *command)
{
	printf("Executing command: %s\n", command);
}

/**
 * process_file - Process commands from a file
 * @filename: The name of the file containing commands
 */

void process_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Cannot open file %s\n", filename);
		exit(EXIT_FAILURE);
	}

	char line[256];
	char *token;
	char *delimiter = "&&";
	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = '\0';

		token = strtok(line, delimiter);
		while (token != NULL)
		{
			process_command(token);
			token = strtok(NULL, delimiter);
		}
	}

	fclose(file);
}
