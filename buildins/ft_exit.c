/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:32:50 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:32:50 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_cmd *cmd, t_shell *shell, int is_child)
{
	if (!is_child)
		ft_putstr_fd("exit\n", 2);
	if (cmd->args[1] == NULL)
		exit(shell->exit_status);
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	if (cmd->args[2] != NULL)
	{
		print_error(shell, "exit", "too many arguments", 1);
		return ;
	}
	exit(ft_atoi(cmd->args[1]) % 256);
}
