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
  const char *builtins[] = {
    "cal",
    "ls",
    "help",
    "exit",
    "cd",
    "env",
    NULL
    };
pid = fork();
if (pid == -1) {
perror("Error in new_node: fork");
return (0);
} else if (pid == 0) {
if (is_builtin(argv[0], builtins)) {
execute_builtin(argv[0], argv);
exit(EXIT_SUCCESS);
} else {
child_process(argv);
exit(EXIT_FAILURE);
}
} else {
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
char *path = "/path/to/executable";
execve(path, argv, NULL);
perror("execve");
}
