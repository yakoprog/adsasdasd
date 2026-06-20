/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:42:20 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/16 16:46:31 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	if (!s)
		return ;
	dst = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
}
