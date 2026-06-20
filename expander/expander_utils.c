/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:03:39 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:54:55 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tokens_for_expand(t_expand *expand)
{
	if (!expand)
		return ;
	if (expand->prefix)
		free(expand->prefix);
	if (expand->suffix)
		free(expand->suffix);
	if (expand->tmp)
		free(expand->tmp);
	if (expand->var_name)
		free(expand->var_name);
	if (expand->var_value)
		free(expand->var_value);
	free(expand);
}

void	reset_expand_fields(t_expand *expand)
{
	if (!expand)
		return ;
	if (expand->prefix)
		free(expand->prefix);
	if (expand->suffix)
		free(expand->suffix);
	if (expand->tmp)
		free(expand->tmp);
	if (expand->var_name)
		free(expand->var_name);
	if (expand->var_value)
		free(expand->var_value);
	expand->prefix = NULL;
	expand->suffix = NULL;
	expand->tmp = NULL;
	expand->var_name = NULL;
	expand->var_value = NULL;
}

void	create_expand(t_expand **expand)
{
	*expand = malloc(sizeof(t_expand));
	if (!*expand)
		return ;
	(*expand)->prefix = NULL;
	(*expand)->suffix = NULL;
	(*expand)->tmp = NULL;
	(*expand)->var_name = NULL;
	(*expand)->var_value = NULL;
}

char	*build_expanded_str(t_expand *exp, char *str)
{
	char	*result;
	char	*val;

	if (exp->var_value)
		val = exp->var_value;
	else
		val = "";
	exp->tmp = ft_strjoin(exp->prefix, val);
	if (!exp->tmp)
		return (NULL);
	result = ft_strjoin(exp->tmp, exp->suffix);
	free(str);
	return (result);
}

char	*execute_expand(char *str, int *i, t_expand *expand, t_shell *shell)
{
	int	val_len;

	expand->prefix = ft_substr(str, 0, *i);
	get_expand_var_value(expand, str, i, shell);
	str = build_expanded_str(expand, str);
	if (expand->var_value)
	{
		val_len = ft_strlen(expand->var_value);
		*i += val_len;
	}
	*i -= 1;
	reset_expand_fields(expand);
	return (str);
}
