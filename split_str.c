#include "shell.h"

/**
 * split_str - split  string into multiple strings
 * @line: string to split
 *
 * Return: pointer to the new array
 */
char **split_str(char *line)
{
int bufsize = 64;
int i = 0;
char **tokens = malloc(bufsize * sizeof(char *));
char *token;

if (!tokens)
{
perror("Allocation error in split_str: tokens");
exit(EXIT_FAILURE);
}
token = strtok(line, TOK_DELIM);
while (token != NULL)
{
if (token[0] == '#')
{
break;
}
tokens[i] = token;
i++;
if (i >= bufsize)
{
bufsize += bufsize;
tokens = realloc(tokens, bufsize *sizeof(char *));
if (!tokens)
{
perror("Reallocation error in split_str: tokens");
exit(EXIT_FAILURE);
}
}
token = strtok(NULL, TOK_DELIM);
}
tokens[i] = NULL;
return (tokens);
}
