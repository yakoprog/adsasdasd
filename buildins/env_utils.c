/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:34:29 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:34:35 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_target_env(char *env_line, char *target, int len)
{
	if (ft_strncmp(env_line, target, len) != 0)
		return (0);
	if (env_line[len] == '=' || env_line[len] == '\0')
		return (1);
	return (0);
}

static int	env_len(char **env)
{
	int	i;

	if (!env)
		return (0);
	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	**export_remove(char *target, char **old_env)
{
	char	**new_env;
	int		len;
	int		i;
	int		j;

	if (!old_env || !target)
		return (old_env);
	len = ft_strlen(target);
	new_env = malloc(sizeof(char *) * (env_len(old_env) + 1));
	if (!new_env)
		return (old_env);
	i = 0;
	j = 0;
	while (old_env[i])
	{
		if (is_target_env(old_env[i], target, len))
			free(old_env[i]);
		else
			new_env[j++] = old_env[i];
		i++;
	}
	new_env[j] = NULL;
	free(old_env);
	return (new_env);
}

char	**export_add(char *new_var, char **old_env)
{
	int		i;
	int		count;
	char	**new_env;

	count = env_len(old_env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (old_env);
	i = 0;
	while (i < count)
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = ft_strdup(new_var);
	new_env[i + 1] = NULL;
	free(old_env);
	return (new_env);
}
