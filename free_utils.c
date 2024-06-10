/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 13:00:39 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/10 13:06:43 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_2d_array(char **array_of_strings)
{
	int	i;

	i = 0;
	while (array_of_strings[i])
	{
		free(array_of_strings[i]);
		i++;
	}
	free(array_of_strings);
}

void	free_struct(t_pipex p)
{
	if (p.path_to_cmd1_executable != NULL)
	{
		free(p.path_to_cmd1_executable);
	}
	if (p.path_to_cmd2_executable != NULL)
	{
		free(p.path_to_cmd2_executable);
	}
	if (p.cmd1 != NULL)
	{
		free_2d_array(p.cmd1);
	}
	if (p.cmd2 != NULL)
	{
		free_2d_array(p.cmd2);
	}
	if (p.paths != NULL)
	{
		free_2d_array(p.paths);
	}
}

void	free_struct_pointer(t_pipex *p)
{
	if (p->path_to_cmd1_executable != NULL)
	{
		free(p->path_to_cmd1_executable);
	}
	if (p->path_to_cmd2_executable != NULL)
	{
		free(p->path_to_cmd2_executable);
	}
	if (p->cmd1 != NULL)
	{
		free_2d_array(p->cmd1);
	}
	if (p->cmd2 != NULL)
	{
		free_2d_array(p->cmd2);
	}
	if (p->paths != NULL)
	{
		free_2d_array(p->paths);
	}
}

void	free_struct_pointer_and_exit_with_errno(t_pipex *p)
{
	free_struct_pointer(p);
	exit (errno);
}

void	free_struct_and_exit_with_errno(t_pipex p)
{
	free_struct(p);
	exit (errno);
}
