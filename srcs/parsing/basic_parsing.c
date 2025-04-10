/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:08:46 by shutan            #+#    #+#             */
/*   Updated: 2025/04/10 16:08:46 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static t_token	*create_token(char *content, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

static int	get_token_type(char *word)
{
	int	type;

	type = TOKEN_WORD;
	if (ft_strncmp(word, "|", 2) == 0)
		type = TOKEN_PIPE;
	else if (ft_strncmp(word, "<", 2) == 0)
		type = TOKEN_REDIR_IN;
	else if (ft_strncmp(word, ">", 2) == 0)
		type = TOKEN_REDIR_OUT;
	else if (ft_strncmp(word, ">>", 3) == 0)
		type = TOKEN_REDIR_APPEND;
	return (type);
}

static void	free_word_array(char **words)
{
	int	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

t_token	*basic_parsing(char *input)
{
	t_token	*tokens;
	char	**words;
	int		i;
	t_token	*new_token;
	int		type;

	tokens = NULL;
	words = ft_split(input, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		type = get_token_type(words[i]);
		new_token = create_token(words[i], type);
		add_token(&tokens, new_token);
		i++;
	}
	free_word_array(words);
	return (tokens);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
} 