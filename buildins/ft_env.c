/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:33:23 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:33:23 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	while ((shell->env)[i] != NULL)
	{
		ft_putendl_fd((shell->env)[i], 1);
		i++;
	}
	shell->exit_status = 0;
}
