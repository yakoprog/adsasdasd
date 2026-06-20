/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 18:17:38 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/03 16:41:12 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = malloc((len1 + len2 + 1) * (sizeof(char)));
	if (!dst)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len1)
		dst[j++] = s1[i++];
	i = 0;
	while (i < len2)
		dst[j++] = s2[i++];
	dst[j] = '\0';
	return (dst);
}
