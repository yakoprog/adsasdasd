/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print_token_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bahkaya <bahkaya@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 21:38:15 by bahkaya           #+#    #+#             */
/*   Updated: 2026/06/20 02:40:02 by bahkaya          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token_error(t_shell *shell, t_token *bad_token)
{
	char	*msg;
	char	*full_msg;

	if (!bad_token)
		msg = ft_strdup("newline");
	else
		msg = ft_strdup(bad_token->value);
	full_msg = ft_strjoin("syntax error near unexpected token `", msg);
	free(msg);
	msg = ft_strjoin(full_msg, "'");
	free(full_msg);
	print_error(shell, NULL, msg, 2);
	free(msg);
}
