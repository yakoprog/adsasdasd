/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:18:44 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/20 02:44:12 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirout_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell)
{
	char	*clean_path;

	*temp = (*temp)->next;
	if (*temp && (*temp)->type == WORD)
	{
		clean_path = remove_quotes(ft_strdup((*temp)->value));
		current_cmd->fd_out = open(clean_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (current_cmd->fd_out == -1)
			print_error(shell, clean_path, strerror(errno), 1);
		free(clean_path);
	}
}

void	append_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell)
{
	char	*clean_path;

	*temp = (*temp)->next;
	if (*temp && (*temp)->type == WORD)
	{
		clean_path = remove_quotes(ft_strdup((*temp)->value));
		current_cmd->fd_out = open(clean_path,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (current_cmd->fd_out == -1)
			print_error(shell, clean_path, strerror(errno), 1);
		free(clean_path);
	}
}

void	redirin_or_not(t_token **temp, t_cmd *current_cmd, t_shell *shell)
{
	char	*clean_path;

	*temp = (*temp)->next;
	if (*temp && (*temp)->type == WORD)
	{
		clean_path = remove_quotes(ft_strdup((*temp)->value));
		current_cmd->fd_in = open(clean_path, O_RDONLY);
		if (current_cmd->fd_in == -1)
			print_error(shell, clean_path, strerror(errno), 1);
		free(clean_path);
	}
}
