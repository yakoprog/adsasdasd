/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 17:22:49 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/08 19:49:15 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_cmptrim(char x, char const *y)
{
	int	i;

	i = 0;
	while (y[i])
	{
		if (y[i] == x)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_cmptrim(s1[start], set))
		start++;
	while (end > start && ft_cmptrim(s1[end - 1], set))
		end--;
	p = malloc(sizeof(char) * (end - start + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (i < end - start)
	{
		p[i] = s1[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
