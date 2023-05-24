#include "shell.h"

/**
 * replace_variable - Replaces variables in a command with their values
 * @state: Pointer to the shell state
 * @command: Command to process
 * Return: Processed command
 */
char *replace_variable(shell_t *state, char *command)
{
	char *result = NULL;
	char *var_ptr, *end_ptr, *value, *temp;
	char variable[MAX_VARIABLE_LENGTH + 1];

	while ((var_ptr = strchr(command, '$')) != NULL)
	{
		result = _realloc(result, strlen(result) + (var_ptr - command) + 1);
		strncat(result, command, var_ptr - command);

		if (*(var_ptr + 1) == '?')
		{
			value = _itoa(state->last_status);
			result = _realloc(result, strlen(result) + strlen(value) + 1);
			strcat(result, value);
			free(value);
			command = var_ptr + 2;
		}
		else if (*(var_ptr + 1) == '$')
		{
			value = _itoa(state->pid);
			result = _realloc(result, strlen(result) + strlen(value) + 1);
			strcat(result, value);
			free(value);
			command = var_ptr + 2;
		}
		else if (*(var_ptr + 1) == '{')
		{
			end_ptr = strchr(var_ptr + 2, '}');
			if (end_ptr)
			{
				strncpy(variable, var_ptr + 2, end_ptr - var_ptr - 2);
				variable[end_ptr - var_ptr - 2] = '\0';
				value = get_variable_value(state->variables, variable);
				if (value)
				{
					result = _realloc(result, strlen(result) + strlen(value) + 1);
					strcat(result, value);
				}
				command = end_ptr + 1;
			}
			else
				command = var_ptr + 1;
		}
		else
			command = var_ptr + 1;
	}

	if (command)
	{
		result = _realloc(result, strlen(result) + strlen(command) + 1);
		strcat(result, command);
	}

	temp = strdup(result);
	free(result);

	return temp;
}
