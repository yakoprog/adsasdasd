/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 14:21:07 by ycinarog          #+#    #+#             */
/*   Updated: 2026/06/18 14:21:07 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_operator(char *input, t_token **tokens)
{
	t_type	type;
	int		len;

	len = 1;
	if (input[0] == '|')
		type = PIPE;
	else if (input[0] == '<' && input[1] == '<')
	{
		len = 2;
		type = HEREDOC;
	}
	else if (input[0] == '>' && input[1] == '>')
	{
		len = 2;
		type = APPEND;
	}
	else if (input[0] == '<')
		type = REDIR_IN;
	else if (input[0] == '>')
		type = REDIR_OUT;
	else
		return (0);
	operator_create(tokens, type, input, len);
	return (len);
}

static int	is_word_break(char c, t_quote_state *qs)
{
	return (!qs->in_sq && !qs->in_dq && (c == ' ' || c == '\t'
			|| c == '|' || c == '<' || c == '>'));
}

static void	update_quote_state(char c, t_quote_state *qs)
{
	if (c == '\'' && !qs->in_dq)
	{
		qs->in_sq = !qs->in_sq;
		if (qs->quote_type == 0)
			qs->quote_type = 1;
	}
	else if (c == '"' && !qs->in_sq)
	{
		qs->in_dq = !qs->in_dq;
		if (qs->quote_type == 0)
			qs->quote_type = 2;
	}
}

int	handle_word(char *input, t_token **tokens)
{
	int				len;
	t_quote_state	qs;

	len = 0;
	qs.in_sq = 0;
	qs.in_dq = 0;
	qs.quote_type = 0;
	while (input[len])
	{
		if (input[len] == '\'' || input[len] == '"')
			update_quote_state(input[len], &qs);
		else if (is_word_break(input[len], &qs))
			break ;
		len++;
	}
	word_create(tokens, input, qs.quote_type, len);
	return (len);
}

void	lexer(char *input, t_token **tokens)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\0')
			break ;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			i += handle_operator(input + i, tokens);
		}
		else
		{
			i += handle_word(input + i, tokens);
		}
	}
}
