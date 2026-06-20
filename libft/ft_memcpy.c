/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 16:06:19 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/01 16:24:11 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destx;
	unsigned char	*srcx;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	destx = (unsigned char *)dest;
	srcx = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		destx[i] = srcx[i];
		i++;
	}
	return (dest);
}
