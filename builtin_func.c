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
write(STDERR_FILENO, "expected argument to \"cd\"\n", strlen("expected argument to \"cd\"\n"));
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

}
#include "shell.h"
/**
* own_help - print help
* @argv: arguments
*
* Return: 1 (success), 0 (otherwise)
*/
int own_help(char **argv)
{
char *builtin_func_list[] = {"cd", "env", "help", "exit"};
unsigned int i = 0;
(void)(**argv);
int fd = open("help.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd == -1)
{
perror("open");
return (0);
}
const char *messages[] = {
"---help simple_shell---",
"Type a command and its arguments, then hit enter",
"Built-in commands:"
 };
ssize_t n;
for (i = 0; i < sizeof(messages) / sizeof(const char *); i++)
{
n = write(fd, messages[i], strlen(messages[i]));
if (n == -1)
{
perror("write");
close(fd);
return (0);
}
}
char buffer[32];
ssize_t write_result;
for (i = 0; i < sizeof(builtin_func_list) / sizeof(char *); i++)
{
n = snprintf(buffer, sizeof(buffer), "  -> %s\n", builtin_func_list[i]);
if (n < 0 || n >= sizeof(buffer))
{
perror("snprintf");
close(fd);
return (0);
}
write_result = write(fd, buffer, n);
if (write_result == -1)
{
perror("write");
close(fd);
return (0);
}
}
const char *end_message = "Use the man command for information on other programs.\n\n";
ssize_t end_write_result = write(fd, end_message, strlen(end_message));
if (end_write_result == -1)
{
perror("write");
close(fd);
return (0);
}
close(fd);
return (-1);
}
