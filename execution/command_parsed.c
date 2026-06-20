/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:22:22 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:22:22 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_executable_file(char *path)
{
	struct stat	st;

	if (access(path, F_OK | X_OK) != 0)
		return (0);
	if (stat(path, &st) != 0)
		return (0);
	if (S_ISDIR(st.st_mode))
		return (0);
	return (1);
}

static char	*ft_find_command(char *input)
{
	char	*command;
	char	*command_parsed;
	int		i;

	i = 0;
	if (is_executable_file(input))
		return (ft_strdup(input));
	while (input[i] != '\0' && input[i] != ' ')
		i++;
	command = ft_substr(input, 0, i);
	if (!command)
		return (NULL);
	command_parsed = ft_strjoin("/", command);
	free(command);
	return (command_parsed);
}

static char	*ft_find_path_location(char **path, char *cmd_parsed)
{
	char	*path_loc;
	int		k;

	k = 0;
	while (path && path[k] != NULL)
	{
		path_loc = ft_strjoin(path[k], cmd_parsed);
		if (is_executable_file(path_loc))
		{
			free(cmd_parsed);
			ft_free_split(path);
			return (path_loc);
		}
		free(path_loc);
		k++;
	}
	free(cmd_parsed);
	ft_free_split(path);
	return (NULL);
}

static char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*put_command(char *input, char **envp)
{
	char	**path;
	char	*cmd_parsed;
	char	*path_str;

	if (!input || !input[0])
		return (NULL);
	if (is_executable_file(input))
		return (ft_strdup(input));
	if (has_slash(input))
		return (NULL);
	cmd_parsed = ft_find_command(input);
	path_str = get_path_from_env(envp);
	if (!cmd_parsed || !path_str)
	{
		free(cmd_parsed);
		return (NULL);
	}
	path = ft_split(path_str, ':');
	return (ft_find_path_location(path, cmd_parsed));
}
