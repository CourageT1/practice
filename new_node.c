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
char *envp[] = { NULL };

pid = fork();
if (pid == 0)
{
/* Child process */
if (execve(argv[0], args, envp) == -1)
{
perror("Error in new_process: execve");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{

/* Error forking */
perror("Error in new_process: fork");
}
else
{
/* Parent process */
waitpid(pid, &status, WUNTRACED);
}
return (-1);
}
