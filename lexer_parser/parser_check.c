/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:45:34 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 13:45:34 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	word_or_not(t_token *temp, t_cmd *current_cmd, int i)
{
	current_cmd->args[i] = ft_strdup(temp->value);
	current_cmd->arg_quoted[i] = (temp->quote_type != 0);
}

static void	skip_to_pipe(t_token **temp)
{
	while (*temp && (*temp)->type != PIPE)
		*temp = (*temp)->next;
}

static int	handle_redirect_token(t_token **temp, t_cmd *current_cmd,
	t_shell *shell)
{
	if ((*temp)->type == REDIR_OUT)
		redirout_or_not(temp, current_cmd, shell);
	else if ((*temp)->type == APPEND)
		append_or_not(temp, current_cmd, shell);
	else if ((*temp)->type == REDIR_IN)
		redirin_or_not(temp, current_cmd, shell);
	else if ((*temp)->type == HEREDOC)
	{
		*temp = (*temp)->next;
		if (*temp && (*temp)->type == WORD)
		{
			if (current_cmd->fd_in > 2)
				close(current_cmd->fd_in);
			current_cmd->fd_in = handle_heredoc((*temp)->value);
		}
	}
	if (current_cmd->fd_in == -1 || current_cmd->fd_out == -1)
		return (0);
	return (1);
}

void	pipe_or_not(t_token **temp, t_cmd *current_cmd, int *i,
	t_shell *shell)
{
	while (*temp && (*temp)->type != PIPE)
	{
		if ((*temp)->type == WORD)
		{
			word_or_not(*temp, current_cmd, *i);
			(*i)++;
		}
		else if (!handle_redirect_token(temp, current_cmd, shell))
			return (skip_to_pipe(temp));
		if (*temp)
			*temp = (*temp)->next;
	}
}
