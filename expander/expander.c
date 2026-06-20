/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:03:59 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:03:59 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		in_sq;
	int		in_dq;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	in_sq = 0;
	in_dq = 0;
	while (str[++i])
	{
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == '"' && !in_sq)
			in_dq = !in_dq;
		else
			new_str[j++] = str[i];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_expand_var_value(t_expand *exp, char *str, int *i, t_shell *shell)
{
	int	j;

	j = *i + 1;
	if (str[j] == '?')
	{
		j++;
		exp->var_value = ft_itoa(shell->exit_status);
	}
	else
	{
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
		exp->var_name = ft_substr(str, *i + 1, j - (*i + 1));
		exp->env_val = get_env_value(exp->var_name, shell->env);
		if (exp->env_val)
			exp->var_value = ft_strdup(exp->env_val);
		else
			exp->var_value = NULL;
	}
	exp->suffix = ft_strdup(str + j);
	if (j > *i + 1)
		return ((char *)1);
	return (0);
}

char	*expand_single_str(char *str, t_shell *shell)
{
	t_expand	*expand;
	int			i;
	int			in_sq;
	int			in_dq;

	create_expand(&expand);
	if (!expand)
		return (str);
	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		else if (str[i] == '"' && !in_sq)
			in_dq = !in_dq;
		if (str[i] == '$' && !in_sq && (ft_isalnum(str[i + 1]) || str[i
					+ 1] == '_' || str[i + 1] == '?'))
			str = execute_expand(str, &i, expand, shell);
		i++;
	}
	free_tokens_for_expand(expand);
	return (str);
}

void	expand_cmd_args(t_cmd *tmp_cmd, t_shell *shell)
{
	int	i;

	i = 0;
	while (tmp_cmd->args[i] != NULL)
	{
		tmp_cmd->args[i] = expand_single_str(tmp_cmd->args[i], shell);
		tmp_cmd->args[i] = remove_quotes(tmp_cmd->args[i]);
		i++;
	}
}

void	strip_empty_unquoted(t_cmd *tmp_cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (tmp_cmd->args[i] != NULL)
	{
		if (tmp_cmd->args[i][0] == '\0' && !tmp_cmd->arg_quoted[i])
			free(tmp_cmd->args[i]);
		else
		{
			tmp_cmd->args[j] = tmp_cmd->args[i];
			tmp_cmd->arg_quoted[j] = tmp_cmd->arg_quoted[i];
			j++;
		}
		i++;
	}
	tmp_cmd->args[j] = NULL;
}
