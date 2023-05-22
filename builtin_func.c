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

typedef struct
{
const char *command;
const char *path;
}
BuiltInCommand;

const BuiltInCommand builtins[] = {
{"ls", "/bin/ls"},
{"cal", "/usr/bin/cal"},
{"cd", "/usr/bin/cd"},
{"env", "/usr/bin/env"},
{"help", "/usr/bin/help"},
{"exit", "/usr/bin/exit"},
{NULL, NULL}
};
/**
* main - entry point
*
* Return: void
*/
int main(void)
{
const char *command = "ls";
const char *path = get_builtin_path(command);

if (path != NULL)
{
const char *message1 = "Command: ";
const char *message2 = "\nPath: ";
write(STDOUT_FILENO, message1, strlen(message1));
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, message2, strlen(message2));
write(STDOUT_FILENO, path, strlen(path));
write(STDOUT_FILENO, "\n", 1);
}
else
{
const char *message = "Command not found: ";
write(STDOUT_FILENO, message, strlen(message));
write(STDOUT_FILENO, command, strlen(command));
write(STDOUT_FILENO, "\n", 1);
}
return (0);
}
return (0);
}

 /**
 * get_builtin - execute a built-in command
 * @command: the built-in command to execute
 * Return: void
 */
void get_builtin_path(char *command)
{
int i = 0;
while (builtins[i].command != NULL)
{
if (strcmp(command, builtins[i].command) == 0)
return builtins[i].path;
i++;
}
return (NULL);
}
