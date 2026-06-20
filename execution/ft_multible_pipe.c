/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multible_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:21:53 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 20:58:04 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	report_path_error(char *cmd_name, t_shell *shell)
{
	struct stat	st;

	if (!has_slash(cmd_name))
	{
		print_error(shell, cmd_name, "command not found", 127);
		exit(127);
	}
	if (stat(cmd_name, &st) != 0)
	{
		print_error(shell, cmd_name, "No such file or directory", 127);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		print_error(shell, cmd_name, "Is a directory", 126);
		exit(126);
	}
	print_error(shell, cmd_name, "Permission denied", 126);
	exit(126);
}

static void	child_execute(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pipe_connection(cmd);
	if (is_builtin(cmd->args[0]))
	{
		execute_builtin(cmd, shell, 1);
		exit(shell->exit_status);
	}
	path = put_command(cmd->args[0], shell->env);
	if (!path)
		report_path_error(cmd->args[0], shell);
	execve(path, cmd->args, shell->env);
	print_error(shell, cmd->args[0], strerror(errno), 126);
	exit(126);
}

static void	ft_dup_except_last(int prev_read_fd)
{
	dup2(prev_read_fd, 0);
	close(prev_read_fd);
}

static void	ft_dup_last(int *fd)
{
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}

void	ft_multiple_pipe(t_cmd *tmp, t_shell *shell, int *id, int *prev_read_fd)
{
	int	fd[2];

	if (tmp->next != NULL)
		pipe(fd);
	*id = fork();
	if (*id == 0)
	{
		if (*prev_read_fd != 0)
			ft_dup_except_last(*prev_read_fd);
		if (tmp->next != NULL)
			ft_dup_last(fd);
		child_execute(tmp, shell);
	}
	else
	{
		if (*prev_read_fd != 0)
			close(*prev_read_fd);
		if (tmp->next != NULL)
		{
			close(fd[1]);
			*prev_read_fd = fd[0];
		}
	}
}
