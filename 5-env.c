#include "shell.h"

/**
 * print_environment - Print the current environment
 * @env: The environment variable array
 */

void print_environment(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * env_shell - Implementation of the env built-in command
 * @env: The environment variable array
 */

void env_shell(char **env)
{
	print_environment(env);
}

/**
 * main - Entry point
 * @argc: The number of command-line arguments
 * @argv: Array containing the command-line arguments
 * @env: The environment variable array
 * Return: 0 on success
 */

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;

	env_shell(env);

	return 0;
}
