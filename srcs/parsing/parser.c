/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:39:26 by shutan            #+#    #+#             */
/*   Updated: 2025/04/14 17:41:20 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_heredoc(t_token *token)
{
	char	*delimiter;
	char	*line;

	if (!token || !token->next)
		return (NULL);
	delimiter = token->next->content;
	ft_printf("heredoc> ");
	while (1)
	{
		line = readline(NULL);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_printf("%s\n", line);
		free(line);
	}
	return (token->next);
}

static t_token	*process_redirections(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->type == TOKEN_HEREDOC)
		return (handle_heredoc(token));
	else if (token->type == TOKEN_REDIR_IN || 
		token->type == TOKEN_REDIR_OUT || 
		token->type == TOKEN_APPEND)
	{
		if (token->next)
			return (token->next);
	}
	return (token);
}

t_token	*parse_command(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type != TOKEN_WORD)
			current = process_redirections(current);
		if (!current)
			break ;
		current = current->next;
	}
	return (tokens);
}

void	parse_input(t_shell *shell, char *input)
{
	if (!input || input[0] == '\0')
		return ;
	add_history(input);
	shell->tokens = tokenize(input);
	if (shell->tokens)
	{
		shell->tokens = parse_command(shell->tokens);
		display_tokens(shell->tokens);
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}