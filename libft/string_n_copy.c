/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_n_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 07:24:35 by mkorpela          #+#    #+#             */
/*   Updated: 2024/05/22 07:27:41 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*string_n_copy(char *dest, char *source, int len)
{
	int	i;

	if (dest == NULL || source == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
