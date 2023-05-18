#include "shell.h"

/**
 * non_prompt - unix command line interpreter
 *
 * Return: void
 */
void non_prompt(void)
{
	char *line;
	char **argv;
	int status = -1;

	do
  {
		line = read_stream();
		argv = split_line(line);
		/* tokenize line */
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
