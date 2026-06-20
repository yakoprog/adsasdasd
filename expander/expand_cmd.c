/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 17:24:31 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/20 02:44:27 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expand_cmds(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = cmds;
	while (tmp_cmd != NULL)
	{
		expand_cmd_args(tmp_cmd, shell);
		strip_empty_unquoted(tmp_cmd);
		tmp_cmd = tmp_cmd->next;
	}
}
