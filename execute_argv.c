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

/**
 * execute_argv - determine if command is built-in or separate process
 * @argv: command and arguments
 *
 * Return: 1 on success (built-in command), 0 otherwise
 */
int execute_argv(char **argv)
{
char *builtin_func_list[] = {
"cd",
"env",
"help",
"exit"
};
int (*builtin_func[])(char **) = {
&own_cd,
&own_env,
&own_help,
&own_exit
};
unsigned int i;

if (argv[0] == NULL)
	return (-1);

for (i = 0; i < sizeof(builtin_func_list) / sizeof(char *); i++)
{
if (strcmp(argv[0], builtin_func_list[i]) == 0)
	return ((*builtin_func[i])(argv));
}
return (new_node(argv));
}
