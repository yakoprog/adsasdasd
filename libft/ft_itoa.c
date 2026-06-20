/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 19:44:55 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/16 16:47:26 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	power(int base, int exp)
{
	int	result;

	result = 1;
	while (exp > 0)
	{
		result *= base;
		exp--;
	}
	return (result);
}

static char	*result_giver(char *result, int n2, int sign, int len)
{
	int	i;
	int	num;

	i = 0;
	if (sign == 1)
		result[i] = '-';
	num = power(10, len - 1);
	while (i < len)
	{
		result[i + sign] = (n2 / num) % 10 + '0';
		num /= 10;
		i++;
	}
	result[i + sign] = '\0';
	return (result);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		n2;
	int		sign;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	sign = 0;
	if (n < 0)
		sign = 1;
	if (n < 0)
		n *= -1;
	n2 = n;
	len = 0;
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len + sign + 1));
	if (!result)
		return (NULL);
	return (result_giver(result, n2, sign, len));
}
