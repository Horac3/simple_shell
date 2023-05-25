#include "shell.h"

/**
 * exit_main_shell - Exit the shell
 */
void exit_main_shell(void)
{
    exit(EXIT_SUCCESS);
}

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
 * execute_main_command - Execute a single command
 * @command: The command to be executed
 */

void execute_main_command(char *command)
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
 * execute_command - Execute a single command
 * @command: The command to be executed
 */

void execute_command_main(char *command)
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
 * main - Entry point of the shell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 * @env: The environment variable array
 * Return: EXIT_SUCCESS if successful, EXIT_FAILURE if fail
 */
int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;

    env_shell(env);

    return EXIT_SUCCESS;
}
