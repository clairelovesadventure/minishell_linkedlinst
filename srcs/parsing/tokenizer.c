/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:38:31 by shutan            #+#    #+#             */
/*   Updated: 2025/04/14 17:38:33 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *content, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->content = ft_strdup(content);
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_token(t_token **head, t_token *new_token)
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
	new_token->prev = current;
}

static int	get_token_type(char *word)
{
	if (!word)
		return (TOKEN_EOF);
	if (ft_strncmp(word, "|", 2) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp(word, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(word, ">>", 2) == 0)
		return (TOKEN_APPEND);
	if (ft_strncmp(word, "<", 2) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(word, ">", 2) == 0)
		return (TOKEN_REDIR_OUT);
	return (TOKEN_WORD);
}

static void	free_word_array(char **words)
{
	int	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

static t_token	*process_words(char **words)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;
	int		type;

	tokens = NULL;
	i = 0;
	while (words[i])
	{
		type = get_token_type(words[i]);
		new_token = create_token(words[i], type);
		if (!new_token)
			return (NULL);
		add_token(&tokens, new_token);
		i++;
	}
	return (tokens);
}

t_token	*tokenize(char *input)
{
	char	**words;
	t_token	*tokens;

	if (!input)
		return (NULL);
	words = ft_split(input, ' ');
	if (!words)
		return (NULL);
	tokens = process_words(words);
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