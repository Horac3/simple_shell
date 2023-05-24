#include "shell.h"

/**
 * print_alias_list - Prints a list of all aliases
 * @aliases: Array of aliases
 */

void print_alias_list(alias_t *aliases)
{
	while (aliases)
	{
		printf("%s='%s'\n", aliases->name, aliases->value);
		aliases = aliases->next;
	}
}

/**
 * print_aliases - Prints the aliases specified by names
 * @aliases: Array of aliases
 * @names: Array of alias names
 */

void print_aliases(alias_t *aliases, char **names)
{
	int i;

	for (i = 0; names[i]; i++)
	{
		alias_t *alias = find_alias(aliases, names[i]);
		if (alias)
			printf("%s='%s'\n", alias->name, alias->value);
	}
}

/**
 * alias_builtin - Handles the alias builtin command
 * @state: Pointer to the shell state
 * @args: Array of command arguments
 * Return: 0 on success, 1 on failure
 */

int alias_builtin(shell_t *state, char **args)
{
	alias_t *new_alias;

	if (!args[1])
	{
		print_alias_list(state->aliases);
		return (0);
	}

	if (args[1] && !args[2])
	{
		print_aliases(state->aliases, args + 1);
		return (0);
	}

	new_alias = create_alias(args[1], args[2]);
	if (!new_alias)
		return (1);

	if (add_alias(&(state->aliases), new_alias) == -1)
	{
		free(new_alias->name);
		free(new_alias->value);
		free(new_alias);
		return (1);
	}

	return (0);
}
