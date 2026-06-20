/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:24:34 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:24:34 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_wait(int id, t_shell *shell)
{
	int	status;

	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->exit_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 1);
		else if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
	}
	while (wait(NULL) > 0)
		;
}

static void	bypass_redirect_io(t_cmd *tmp, int *original_out)
{
	*original_out = dup(1);
	if (tmp->fd_in > 2)
	{
		close(tmp->fd_in);
		tmp->fd_in = 0;
	}
	if (tmp->fd_out != 1)
	{
		dup2(tmp->fd_out, 1);
		close(tmp->fd_out);
		tmp->fd_out = 1;
	}
}

int	ft_bypass(t_cmd *tmp, t_shell *shell)
{
	int	original_out;

	if (tmp != NULL && tmp->next == NULL && is_builtin(tmp->args[0]))
	{
		if (tmp->fd_in == -1 || tmp->fd_out == -1)
		{
			shell->exit_status = 1;
			return (1);
		}
		bypass_redirect_io(tmp, &original_out);
		ignore_sigint_parent();
		execute_builtin(tmp, shell, 0);
		restore_sigint_parent();
		dup2(original_out, 1);
		close(original_out);
		return (1);
	}
	return (0);
}

void	after_lexer(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*tmp;
	int		id;
	int		prev_read_fd;

	prev_read_fd = 0;
	id = 0;
	tmp = cmds;
	if (ft_bypass(tmp, shell))
		return ;
	ignore_sigint_parent();
	while (tmp != NULL)
	{
		ft_multiple_pipe(tmp, shell, &id, &prev_read_fd);
		tmp = tmp->next;
	}
	ft_wait(id, shell);
	restore_sigint_parent();
}
