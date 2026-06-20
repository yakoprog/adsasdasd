/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:31:00 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:31:00 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_error(t_shell *shell, char *cmd, char *msg, int err_code)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	shell->exit_status = err_code;
	return (err_code);
}

void	export_error(t_shell *shell, char *cmd_name, char *bad_arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(bad_arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	shell->exit_status = 1;
}

int	is_valid_env_name(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	pipe_error(t_token *tokens, t_shell *shell)
{
	t_token	*tmp;

	tmp = tokens;
	if (!tmp->next || tmp->next->type == PIPE)
	{
		print_error(shell, NULL, "syntax error near unexpected token `|'", 2);
		return (0);
	}
	return (1);
}
