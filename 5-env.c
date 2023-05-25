#include <stdio.h>
#include "shell.h"

/**
 * print_environment_5 - Print the current environment
 * @env: The environment variable array
 */

void print_environment_5(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * env_shell_5 - Implementation of the env built-in command
 * @env: The environment variable array
 */

void env_shell_5(char **env)
{
	print_environment(env);
}

int env_5(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;

	env_shell(env);

	return (0);
}
