#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

/**
 * custom_getline - gets the line arguments in a shell
 *
 * Return: returns the input
 */


char *custom_getline(void)
{
	static char buffer[MAX_INPUT_SIZE];
	static size_t buffer_index;
	static ssize_t bytes_read;

	char *input = (char *)malloc(MAX_INPUT_SIZE);

	if (input == NULL)
	{
		perror("malloc() failed");
		exit(EXIT_FAILURE);
	}
	if (buffer_index >= (size_t)bytes_read)
	{
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer));
		if (bytes_read == -1)
		{
			perror("read() failed");
			exit(EXIT_FAILURE);
		}
		buffer_index = 0;
		if (bytes_read == 0)
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
	}
	while (buffer_index <
			(size_t)bytes_read && buffer[buffer_index] != '\n')
	{
		input[buffer_index] = buffer[buffer_index];
		buffer_index++;
	}
	input[buffer_index] = '\0';

	if (buffer_index < (size_t)bytes_read)
	{
		buffer_index++;
	}
	return (input);
}
