#include "shell.h"

/**
 * scan_stream - Read a line from stream.
 *
 * Return: Pointer to read line.
 */
char *scan_stream(void)
{
	int n = 1024;
	int i = 0;
	char *line = malloc(sizeof(char) * n);
	int character;

	if (line == NULL)
	{
		perror("allocation error in read_stream");
		exit(EXIT_FAILURE);
	}

	while (1)
	{
		character = getchar();

		if (character == EOF)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		else if (character == '\n')
		{
			line[i] = '\0';
			return line;
		}
		else
		{
			line[i] = character;
		}

		i++;

		if (i >= n)
		{
			n += n;
			line = realloc(line, bufsize);
			if (line == NULL)
			{
				perror("reallocation error in read_stream");
				exit(EXIT_FAILURE);
			}
		}
	}
}
