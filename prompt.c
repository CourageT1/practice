#include "shell.h"

/**
 * prompt - UNIX command line interpreter
 *
 * Return: void
 */
void prompt(void)
{
	char *line;
	char **argv;
	int status = -1;

	do {
		write(STDOUT_FILENO, "simple_prompt$ ", strlen("simple_prompt$ "));
		line = read_line(); /* read line from stdin */
		argv = split_line(line); /* tokenize line */
		status = execute_argv(argv);
		/* avoid memory leaks */
		free(line);
		free(argv);
		/* exit with status */
		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}

