#include "shell.h"

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
