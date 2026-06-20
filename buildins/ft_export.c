/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:32:36 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:32:36 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../minishell.h"

static void	sort_env_copy(char **env, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strncmp(env[j], env[j + 1], ft_strlen(env[j])) > 0)
			{
				tmp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

static int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static void	print_export_line(char *env_line)
{
	char	*eq;
	int		i;

	eq = ft_strchr(env_line, '=');
	ft_putstr_fd("declare -x ", 1);
	if (!eq)
	{
		ft_putendl_fd(env_line, 1);
		return ;
	}
	i = 0;
	while (env_line + i != eq)
	{
		ft_putchar_fd(env_line[i], 1);
		i++;
	}
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(eq + 1, 1);
	ft_putendl_fd("\"", 1);
}

void	print_export_sorted(t_shell *shell)
{
	char	**copy;
	int		count;
	int		i;

	count = env_count(shell->env);
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return ;
	i = 0;
	while (i < count)
	{
		copy[i] = shell->env[i];
		i++;
	}
	copy[i] = NULL;
	sort_env_copy(copy, count);
	i = 0;
	while (i < count)
	{
		print_export_line(copy[i]);
		i++;
	}
	free(copy);
}

void	ft_export(t_cmd *cmd, t_shell *shell)
{
	int	i;

	shell->exit_status = 0;
	if (cmd->args[1] == NULL)
	{
		print_export_sorted(shell);
		return ;
	}
	i = 1;
	while (cmd->args[i] != NULL)
	{
		if (is_valid_env_name(cmd->args[i]) == 0)
			export_error(shell, "export", cmd->args[i]);
		else
			shell->env = export_add(cmd->args[i], shell->env);
		i++;
	}
}
