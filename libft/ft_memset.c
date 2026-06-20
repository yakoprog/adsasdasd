/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:59:35 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/01 16:50:08 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	size_t			i;

	if (!s)
		return (NULL);
	dst = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		dst[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
