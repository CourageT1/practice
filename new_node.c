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
char *envp[] = {
	"HOME=/home/user",
	"PATH=/usr/local/bin:/usr/bin:/bin",
	"USER=user",
	NULL
};

pid = fork();
if (pid == -1)
{
/* Error forking */
perror("Error in new_node: fork");
return (0);
}
else if (pid == 0)
{
/* Child process */
if (is_builtin(argv[0], builtins))
{
execute_builtin(argv[0], argv);
exit(EXIT_SUCCESS);
}
else
{
if (execve(argv[0], argv, envp) == -1)
{
perror("Error in new_node: execve");
exit(EXIT_FAILURE);
}
}
}
else
{
/* Parent process */
waitpid(pid, &status, WUNTRACED);
}
return (1);
}
