/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 13:37:08 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 13:37:08 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	operator_create(t_token **tokens, t_type type, char *input, int len)
{
	char	*content;
	t_token	*new_node;

	content = ft_substr(input, 0, len);
	if (!content)
		return ;
	new_node = new_token(content, type, 0);
	if (!new_node)
	{
		free(content);
		return ;
	}
	ft_token_add_back(tokens, new_node);
}

void	word_create(t_token **tokens, char *input, int quote_type, int len)
{
	char	*content;
	t_token	*new_node;

	content = ft_substr(input, 0, len);
	if (!content)
		return ;
	new_node = new_token(content, WORD, quote_type);
	if (!new_node)
	{
		free(content);
		return ;
	}
	ft_token_add_back(tokens, new_node);
}

t_token	*new_token(char *value, t_type type, int quote_type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->quote_type = quote_type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	ft_token_add_back(t_token **tokens, t_token *new_node)
{
	t_token	*temp;

	if (*tokens == NULL)
	{
		*tokens = new_node;
		return ;
	}
	temp = *tokens;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
}
