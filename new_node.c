#include "shell.h"

/**
 * new_node - create a new process(node)
 * @argv: array of strings that contains the command and its flags
 *
 * Return: 1 if success, 0 otherwise
 */
int new_node(char **argv)
{
	pid_t pid;
	int status;
	int run = 0;

	pid = fork();
	if (pid == 0)
	{
		/* Child process */
		int devNull = open("/dev/null", O_WRONLY);
		dup2(devNull, STDERR_FILENO);
		close(devNull);
		
		if (execve(argv[0], argv, NULL) == -1)
		{
			++run;
		}
	}
	else if (pid < 0)
	{
		/* Error forking */
		perror("Error in new_node: fork");
		return (0);
	}
	else
	{
		/* Parent process */
	       	
			waitpid(pid, &status, 0);
		}

	return (1);
}
