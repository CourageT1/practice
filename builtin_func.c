#include "shell.h"
#include <unistd.h>  // Include the <unistd.h> header for the write function

/**
 * own_exit - causes normal process termination
 * @args: empty args
 *
 * Return: 0 to terminate the process
 */
int own_exit(char **args)
{
    /* exit with status */
    if (args[1])
    {
        return atoi(args[1]);
    }
    /* exit success */
    else
    {
        return 0;
    }
}

/**
 * own_cd - changes the working dir of the current shell execution env
 * @args: target directory
 *
 * Return: 1 on success, 0 otherwise.
 */
int own_cd(char **args)
{
    if (args[1] == NULL)
    {
        write(STDERR_FILENO, "expected argument to \"cd\"\n", strlen("expected argument to \"cd\"\n"));
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("error in own_cd.c: changing dir\n");
        }
    }
    return -1;
}

/**
 * own_env - function that prints environment variables
 * @args: arguments
 *
 * Return: 1 on success, 0 otherwise
 */
int own_env(char **args)
{
    int i = 0;
    (void)(**args);

    while (environ[i])
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
        i++;
    }
    return -1;
}

/**
 * own_help - print help
 * @args: arguments
 *
 * Return: 1 on success, 0 otherwise
 */
int own_help(char **args)
{
    char *builtin_func_list[] = {
        "cd",
        "env",
        "help",
        "exit"
    };
    long unsigned int i = 0;
    (void)(**args);

    write(STDOUT_FILENO, "\n---help simple_shell---\n", strlen("\n---help simple_shell---\n"));
    write(STDOUT_FILENO, "Type a command and its arguments, then hit enter\n", strlen("Type a command and its arguments, then hit enter\n"));
    write(STDOUT_FILENO, "Built-in commands:\n", strlen("Built-in commands:\n"));
    for (; i < sizeof(builtin_func_list) / sizeof(char *); i++)
    {
        char buffer[32];
        int n = snprintf(buffer, sizeof(buffer), "  -> %s\n", builtin_func_list[i]);
        write(STDOUT_FILENO, buffer, n);
    }
    write(STDOUT_FILENO, "Use the man command for information on other programs.\n\n", strlen("Use the man command for information on other programs.\n\n"));
    return -1;
}
