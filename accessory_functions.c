/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_error_code_into_struct.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:05:34 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/11 08:25:02 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_error_code_into_struct(t_pipex *p, int cmd_number, int error_code)
{
	if (cmd_number == 1)
	{
		p->err_in_cmd1 = error_code;
	}
	else
	{
		p->err_in_cmd2 = error_code;
	}
}

char	**find_paths_to_executables(t_pipex p)
{
	char	**environ_paths;
	int		i;

	i = 0;
	environ_paths = NULL;
	while (p.envp[i])
	{
		if (ft_strncmp(p.envp[i], "PATH=", 5) == 0)
		{
			environ_paths = ft_split(p.envp[i] + 5, ':');
			if (environ_paths == NULL)
			{
				exit (1);
			}
			break ;
		}
		i++;
	}
	return (environ_paths);
}
