#include "shell.h"

/**
 * own_exit - causes process termination
 * @argv: empty args
 *
 * Return: 0 to terminate process
 */
int own_exit(char **argv)
{
if (argv[1])
{
	return (atoi(argv[1]));
}
else
{
return (0);
}
}

/**
 * own_cd - changes the working dir of the current shell execution env
 * @argv: target directory
 *
 * Return: 1 on success, 0 otherwise.
 */
int own_cd(char **argv)
{
if (argv[1] == NULL)
{
write(STDERR_FILENO, "expected argument to \"cd\"\n",
		strlen("expected argument to \"cd\"\n"));
}
else
{
if (chdir(argv[1]) != 0)
{
perror("error in own_cd.c: changing dir\n");
}
}
return (-1);
}

/**
 * own_env - function that prints environment variables
 * @argv: arguments
 *
 * Return: 1 on success, 0 otherwise
 */
int own_env(char **argv)
{
int i = 0;
(void)(**argv);

while (environ[i])
{
write(STDOUT_FILENO, environ[i], strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
i++;
}
return (-1);
}

/**
 * own_help - print help
 * @argv: arguments
 *
 * Return: 1 on success, 0 otherwise
 */
int own_help(char **argv)
{
const char *builtin_func_list[] = {
"cd",
"env",
"help",
"exit"
};
unsigned int i = 0;
(void)(**argv);
{
write(STDOUT_FILENO, "\n---help simple_shell---\n",
		strlen("\n---help simple_shell---\n"));
write(STDOUT_FILENO, "Type a command and its arguments, then hit enter\n",
		strlen("Type a command and its arguments, then hit enter\n"));
write(STDOUT_FILENO, "Built-in commands:\n",
		strlen("Built-in commands:\n"));

for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
{
char buffer[32];
int n = snprintf(buffer, sizeof(buffer), "  -> %s\n", builtin_func_list[i]);
write(STDOUT_FILENO, buffer, n);
}
write(STDOUT_FILENO, "Use man command for information on other programs.\n\n",
		strlen("Use the man command for information on other programs.\n\n"));
return (-1);
}
return (0);
}
/**
 * execute_builtin - execute a built-in command
 * @command: the built-in command to execute
 * @argv: array of strings that contains the command and its arguments
 */
void execute_builtin(char *command, char **argv)
{
if (strcmp(command, "cd") == 0)
{
if (argv[1] != NULL)
{
if (chdir(argv[1]) != 0)
{
perror("chdir");
}
}
else
{
write(STDOUT_FILENO, "cd: missing argument\n", 21);
}
}
else if (strcmp(command, "env") == 0)
{
extern char **environ;
char **env = environ;
while (*env)
{
write(STDOUT_FILENO, *env, strlen(*env));
write(STDOUT_FILENO, "\n", 1);
env++;
}
}
else if (strcmp(command, "help") == 0)
{
write(STDOUT_FILENO, "Help message\n", 13);
}
else if (strcmp(command, "exit") == 0)
{
exit(0);
}
else
{
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, ": command not found\n", 20);
}
}
/**
 * is_builtin - check if a command is a built-in command
 * @command: the command to check
 * @builtins: array of built-in commands
 *
 * Return: 1 if the command is a built-in, 0 otherwise
 */
int is_builtin(char *command, char **builtins)
{
int i;
for (i = 0; builtins[i] != NULL; i++)
{
if (strcmp(command, builtins[i]) == 0)
return (1);
}
return (0);
}
