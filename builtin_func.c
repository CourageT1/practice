#include "shell.h"

/**
 * own_exit - couses normal process termination
 * @args: empty args
 *
 * Return: 0 to terminate the process
 */
int own_exit(char **args)
{
	/* exit with status */
	if (args[1])
	{
		return (atoi(args[1]));
	}
	/* exit success */
	else
	{
		return (0);
	}
}

/**
 * own_cd - changes the working dir of the current shell executon env
 * @args: target directory
 *
 * Return: 1 one success, 0 otherwise.
 */
int own_cd(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "expected argument to \"cd\"\n");
	}
	else
	{
		if (chdir(args[1]) != 0)
		{
			perror("error in own_cd.c: changing dir\n");
		}
	}
	return (-1);
}

