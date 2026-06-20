/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycinarog <ycinarog@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:01:23 by ycinarog          #+#    #+#             */
/*   Updated: 2025/06/14 20:00:48 by ycinarog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*obj;

	obj = (t_list *)malloc(sizeof(t_list));
	if (!obj)
		return (NULL);
	obj->next = NULL;
	obj->content = content;
	return (obj);
}
