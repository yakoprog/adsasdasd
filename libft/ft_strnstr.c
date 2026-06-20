/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 21:11:41 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/01 13:34:53 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*temp_b;
	char	*temp_l;
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	temp_b = (char *)big;
	temp_l = (char *)little;
	while (temp_b[i] && i < len)
	{
		j = 0;
		while (temp_b[i + j] == temp_l[j] && (i + j) < len && temp_l[j] != '\0')
		{
			j++;
		}
		if (temp_l[j] == '\0')
			return (temp_b + i);
		i++;
	}
	return (NULL);
}
