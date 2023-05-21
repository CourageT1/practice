#include "shell.h"

/**
 * main - function that checks if our shell is called
 *
 * Return: 0 on success
 */
int main(void)
{
	/* determines if file descriptor is associated with a terminal */
	if (isatty(STDIN_FILENO) == 1)
	{
		prompt();
	}
	else
	{
		non_prompt();
	}
	return (0);
}
