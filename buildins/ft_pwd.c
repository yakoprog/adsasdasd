/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:32:18 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:32:18 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_shell *shell)
{
	char	cwd[1024];
	char	*pwd_val;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_putendl_fd(cwd, 1);
		shell->exit_status = 0;
	}
	else
	{
		pwd_val = get_env_value("PWD", shell->env);
		if (pwd_val)
		{
			ft_putendl_fd(pwd_val, 1);
			shell->exit_status = 0;
		}
		else
			print_error(shell, "pwd", strerror(errno), 1);
	}
}
