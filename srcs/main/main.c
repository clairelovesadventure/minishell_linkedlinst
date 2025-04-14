/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shutan <shutan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 15:30:18 by shutan            #+#    #+#             */
/*   Updated: 2025/04/14 17:43:27 by shutan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env_init(envp);
	shell->exit_status = 0;
	shell->running = 1;
	return (shell);
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	free_env(shell->env);
	free(shell);
}

static void	display_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	ft_putstr_fd("Parsed tokens:\n", 1);
	while (current)
	{
		ft_putstr_fd("  Token: '", 1);
		ft_putstr_fd(current->content, 1);
		ft_putstr_fd("', Type: ", 1);
		ft_putnbr_fd(current->type, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

static void	process_input(t_shell *shell, char *input)
{
	if (!input || input[0] == '\0')
		return ;
	add_history(input);
	shell->tokens = basic_parsing(input);
	display_tokens(shell->tokens);
	free_tokens(shell->tokens);
	shell->tokens = NULL;
	if (ft_strncmp(input, "exit", 4) == 0 
		&& (input[4] == '\0' || input[4] == ' '))
		shell->running = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*input;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	if (!shell)
	{
		ft_putstr_fd("Error initializing shell\n", 2);
		return (1);
	}
	while (shell->running)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		process_input(shell, input);
		free(input);
	}
	cleanup_shell(shell);
	clear_history();
	return (0);
}
