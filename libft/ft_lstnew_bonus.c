/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:49:44 by mkorpela          #+#    #+#             */
/*   Updated: 2024/02/05 11:18:55 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node1;

	node1 = (t_list *)malloc(sizeof(t_list));
	if (node1 == NULL)
	{
		return (NULL);
	}
	node1->content = content;
	node1->next = NULL;
	return (node1);
}
