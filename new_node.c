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

pid = fork();
if (pid == -1) {
write(STDERR_FILENO, "Error in new_node: fork\n", 24);
return (0);
}
else if (pid == 0)
{
if (is_builtin(argv[0]))
{
const char *path = get_builtin_path(argv[0]);
if (path != NULL)
{
execve(path, argv, NULL);
}
else
{
const char *message1 = "Unknown command: ";
const char *message2 = "\n";
write(STDERR_FILENO, message1, strlen(message1));
write(STDERR_FILENO, argv[0], strlen(argv[0]));
write(STDERR_FILENO, message2, strlen(message2));
}
}
else
{
child_process(argv);
}
_exit(EXIT_SUCCESS);
}else
{
waitpid(pid, &status, WUNTRACED);
}
return (1);
}

/**
* child_process - creates process to execute command
* @argv: array to execute
*
* Return: void
*/
void child_process(char **argv)
{
execve(argv[0], argv, NULL);
write(STDERR_FILENO, "execve error\n", 13);
_exit(EXIT_FAILURE);
}
