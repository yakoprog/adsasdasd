/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:31:33 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:31:33 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	shell->exit_status = 0;
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (is_valid_env_name(cmd->args[i]) == 0
			|| ft_strchr(cmd->args[i], '='))
		{
			export_error(shell, "unset", cmd->args[i]);
		}
		else
		{
			shell->env = export_remove(cmd->args[i], shell->env);
		}
		i++;
	}
}
