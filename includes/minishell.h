#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"  /* Include libft.h */

/* Token types */
# define TOKEN_EMPTY 0
# define TOKEN_WORD 1
# define TOKEN_PIPE 2
# define TOKEN_REDIR_IN 3
# define TOKEN_REDIR_OUT 4
# define TOKEN_REDIR_APPEND 5

/* Basic token structure */
typedef struct s_token
{
    char *content;             /* Token content (string) */
    int type;                  /* Token type */
    struct s_token *next;      /* Next token in linked list */
} t_token;

/* Environment variable structure */
typedef struct s_env
{
    char *value;               /* Environment variable (NAME=VALUE) */
    struct s_env *next;        /* Next env variable in linked list */
} t_env;

/* Main shell structure */
typedef struct s_shell
{
    t_token *tokens;           /* Linked list of tokens */
    t_env *env;                /* Environment variables list */
    int exit_status;           /* Last command's exit status */
    int running;               /* Shell running flag */
} t_shell;

/* Function prototypes */
/* Environment functions */
t_env *env_init(char **envp);
void free_env(t_env *env);

/* Parsing functions */
t_token *basic_parsing(char *input);
void free_tokens(t_token *tokens);

#endif
