/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:55:16 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/11 08:23:47 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_struct_and_error_msg(t_pipex p, char *error_msg)
{
	free_struct(p);
	if (error_msg != NULL)
	{
		if (write(2, error_msg, ft_strlen(error_msg)) == -1)
		{
			perror("free_struct_and_error_msg - function");
			exit (errno);
		}
	}
}

void	pipex_manual_err_msg(char *err_msg, char *where, t_pipex p)
{
	if (write(2, "pipex: ", 7) == -1)
	{
		free_struct_and_exit_with_errno(p);
	}
	if (write(2, err_msg, ft_strlen(err_msg)) == -1)
	{
		free_struct_and_exit_with_errno(p);
	}
	if (write(2, ": ", 2) == -1)
	{
		free_struct_and_exit_with_errno(p);
	}
	if (write(2, where, ft_strlen(where)) == -1)
	{
		free_struct_and_exit_with_errno(p);
	}
	if (write(2, "\n", 1) == -1)
	{
		free_struct_and_exit_with_errno(p);
	}
}

void	pipex_manual_err_msg_2(char *err_msg, char *where, t_pipex *p)
{
	if (write(2, "pipex: ", 7) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, err_msg, ft_strlen(err_msg)) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, ": ", 2) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, where, ft_strlen(where)) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, "\n", 1) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
}

void	pipex_err_msg(char *where_err_msg, t_pipex *p)
{
	char	*errno_error_msg;

	if (write(2, "pipex: ", 7) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	errno_error_msg = strerror(errno);
	if (write(2, errno_error_msg, ft_strlen(errno_error_msg)) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, ": ", 2) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, where_err_msg, ft_strlen(where_err_msg)) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
	if (write(2, "\n", 1) == -1)
	{
		free_struct_pointer_and_exit_with_errno(p);
	}
}
