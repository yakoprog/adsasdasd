/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:43:47 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 13:46:11 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_sigint(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

int	heredoc_cleanup(int *p_fd, int stdin_copy)
{
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	if (p_fd[0] != -1)
		close(p_fd[0]);
	if (p_fd[1] != -1)
		close(p_fd[1]);
	signal(SIGINT, handle_sigint);
	return (-1);
}

int	heredoc_read_loop(int *p_fd, char *delim, int stdin_copy)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_signal == SIGINT)
				return (heredoc_cleanup(p_fd, stdin_copy));
			break ;
		}
		if (ft_strncmp(line, delim, ft_strlen(delim) + 1) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, p_fd[1]);
		ft_putstr_fd("\n", p_fd[1]);
		free(line);
	}
	return (0);
}
