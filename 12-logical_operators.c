#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

(
	printf("Executing command: %s\n", command);
	)

(
	FILE *file = fopen(filename, "r");
	char line[256];

	if (file == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), file))
	{
		line[strcspn(line, "\n")] = '\0';
		process_command(line);
	}

	fclose(file);
	)

	(
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return EXIT_FAILURE;
	}

	process_file(argv[1]);

	return EXIT_SUCCESS;
	)
