/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:34:46 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:34:46 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(char *key, char **envp)
{
	int	i;
	int	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, key_len) == 0)
		{
			if (envp[i][key_len] == '=')
				return (envp[i] + key_len + 1);
			if (envp[i][key_len] == '\0')
				return ("");
		}
		i++;
	}
	return (NULL);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
