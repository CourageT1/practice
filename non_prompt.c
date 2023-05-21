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
		line = scan_stream();
		argv = split_str(line);
		status = execute_argv(argv);
		free(line);
		free(argv);
		if (status >= 0)
		{
			exit(status);
		}
	} while (status == -1);
}
