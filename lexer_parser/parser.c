/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:00:31 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:00:36 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_heredoc(char *delimiter)
{
	int	p_fd[2];
	int	stdin_copy;

	if (pipe(p_fd) == -1)
		return (-1);
	stdin_copy = dup(STDIN_FILENO);
	signal(SIGINT, heredoc_sigint);
	if (heredoc_read_loop(p_fd, delimiter, stdin_copy) == -1)
		return (-1);
	close(stdin_copy);
	close(p_fd[1]);
	signal(SIGINT, handle_sigint);
	return (p_fd[0]);
}

t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->fd_in = 0;
	cmd->fd_out = 1;
	cmd->next = NULL;
	return (cmd);
}

void	cmd_add_back(t_cmd **cmds, t_cmd *new_node)
{
	t_cmd	*temp;

	if (*cmds == NULL)
	{
		*cmds = new_node;
		return ;
	}
	temp = *cmds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	return ;
}

static void	process_single_command(t_token **temp, t_cmd **cmds, t_shell *shell)
{
	t_token	*scan;
	t_cmd	*current_cmd;
	int		i;
	int		arg_count;

	current_cmd = new_cmd_node();
	cmd_add_back(cmds, current_cmd);
	arg_count = 0;
	scan = *temp;
	while (scan && scan->type != PIPE)
	{
		if (scan->type >= REDIR_IN && scan->type <= APPEND)
			scan = scan->next;
		else if (scan->type == WORD)
			arg_count++;
		if (scan)
			scan = scan->next;
	}
	current_cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	current_cmd->arg_quoted = malloc(sizeof(int) * (arg_count + 1));
	if (!current_cmd->args)
		return ;
	i = 0;
	pipe_or_not(temp, current_cmd, &i, shell);
	current_cmd->args[i] = NULL;
}

void	parse_tokens(t_token *tokens, t_cmd **cmds, t_shell *shell)
{
	t_token	*temp;

	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			temp = temp->next;
			continue ;
		}
		process_single_command(&temp, cmds, shell);
	}
}
