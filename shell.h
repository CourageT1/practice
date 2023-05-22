#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define TOK_DELIM " \t\r\n\a\""
extern char **environ;

void prompt(void);
void non_prompt(void);

char *scan_line(void);
char **split_str(char *line);
int execute_argv(char **argv);
int new_node(char **argv);
char *scan_stream(void);
int own_cd(char **argv);
int own_exit(char **argv);
int own_env(char **argv);
int own_help(char **argv);
int is_builtin(const char *command);
void get_builtin_path(char *command);
void child_process(char **argv);

#endif
