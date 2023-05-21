#include "shell.h"

/**
 * scan_line - Reads line from stdin.
 *
 * Return: Pointer to a string with the line content.
 */
char *scan_line(void)
{
char *line = NULL;
size_t bufsize = 0;

if (getline(&line, &bufsize, stdin) == -1)
{
if (feof(stdin))
{
free(line);
exit(EXIT_SUCCESS);
}
else
{
free(line);
perror("Error while reading the line from stdin");
exit(EXIT_FAILURE);
}
}
return (line);
}
