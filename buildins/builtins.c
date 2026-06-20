/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:35:14 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:35:14 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_cmd *cmd, t_shell *shell, int is_child)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		ft_env(shell);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		ft_exit(cmd, shell, is_child);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		ft_cd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		ft_echo(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		ft_export(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		ft_unset(cmd, shell);
}
