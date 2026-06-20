/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:37:15 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:37:15 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

static void	setup_shell(char **envp, t_shell *shell)
{
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	increment_shlvl(shell);
	init_signals();
}

static void	process_command_line(char *input, t_shell *shell)
{
	t_token	*token_list;
	t_cmd	*cmd_list;

	if (!check_quotes(input, shell))
		return ;
	token_list = NULL;
	cmd_list = NULL;
	lexer(input, &token_list);
	if (!check_syntax(token_list, shell))
	{
		free_tokens(token_list);
		return ;
	}
	parse_tokens(token_list, &cmd_list, shell);
	expand_cmds(cmd_list, shell);
	after_lexer(cmd_list, shell);
	free_tokens(token_list);
	free_cmds(cmd_list);
}

static void	shell_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (g_signal == SIGINT)
		{
			shell->exit_status = 130;
			g_signal = 0;
		}
		if (input == NULL || ft_strncmp(input, "exit", 5) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			if (input != NULL)
				free(input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			process_command_line(input, shell);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)av;
	if (ac != 1)
	{
		print_error(&shell, NULL, "Minishell does not take arguments", 1);
		return (1);
	}
	setup_shell(envp, &shell);
	shell_loop(&shell);
	ft_free_split(shell.env);
	clear_history();
	return (shell.exit_status);
}
