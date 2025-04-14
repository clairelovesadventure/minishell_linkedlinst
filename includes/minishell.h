/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:37:20 by shutan            #+#    #+#             */
/*   Updated: 2025/04/14 17:42:11 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "../libft/libft.h"  /* Include libft.h */

/* Token types */
# define TOKEN_WORD		1
# define TOKEN_PIPE		2
# define TOKEN_REDIR_IN		3
# define TOKEN_REDIR_OUT	4
# define TOKEN_HEREDOC		5
# define TOKEN_APPEND		6
# define TOKEN_EOF		7

/* Structures */
typedef struct s_token
{
	char			*content;
	int			type;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

/* Environment variable structure */
typedef struct s_env
{
	char *value;               /* Environment variable (NAME=VALUE) */
	struct s_env *next;        /* Next env variable in linked list */
} t_env;

/* Main shell structure */
typedef struct s_shell
{
	t_token			*tokens;
	t_env			*env;
	int			exit_status;
	int			running;
}	t_shell;

/* Function prototypes */
/* Environment functions */
t_env *env_init(char **envp);
void free_env(t_env *env);

/* Token functions */
t_token		*create_token(char *content, int type);
void		add_token(t_token **head, t_token *new_token);
void		free_tokens(t_token *tokens);
t_token		*tokenize(char *input);

/* Shell functions */
void		cleanup_shell(t_shell *shell);

/* New function declaration */
t_token         *basic_parsing(char *input);

#endif
