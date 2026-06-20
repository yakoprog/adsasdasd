/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:32:05 by ycinarog          #+#    #+#             */
/*   Updated: 2025/05/31 19:58:58 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp_s;
	size_t			i;

	if (!s)
		return (NULL);
	temp_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)c == temp_s[i])
			return (temp_s + i);
		i++;
	}
	return (NULL);
}
