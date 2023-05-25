#include <stdlib.h>
#include "shell.h"

/**
 * exit_shell_4 - Exit the shell
 * exit_4 - Exit shell
 */

void exit_shell_4(void)
{
	exit(EXIT_SUCCESS);
}
int exit_4(int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;
    (void)env;

    exit_shell();

    return 0;
}
