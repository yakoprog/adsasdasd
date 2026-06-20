/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 13:28:11 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/16 16:44:59 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*srcx;
	unsigned char	*destx;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	srcx = (unsigned char *)src;
	destx = (unsigned char *)dest;
	i = n;
	if (dest < src)
	{
		ft_memcpy(destx, srcx, i);
		return (dest);
	}
	while (i > 0)
	{
		destx[i - 1] = srcx[i - 1];
		i--;
	}
	return (dest);
}
