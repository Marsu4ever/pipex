/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:18:31 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/29 18:28:08 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	clean_up1_and_exit(t_pipex p, int pipefd_in, int pipefd_out)
{
	free_struct(p);
	close(pipefd_in);
	close(pipefd_out);
	exit (1);
}

static void	clean_up2_and_exit(t_pipex p, int pipefd_in, int pipefd_out)
{
	free_struct(p);
	close(pipefd_in);
	close(pipefd_out);
	exit (errno);
}

static void	clean_up3_and_exit(t_pipex p, int fd_in, int fd_out, int fd_open)
{
	free_struct(p);
	close(fd_in);
	close(fd_out);
	close(fd_open);
	exit (errno);
}

void	child_one(t_pipex p, int *pipefd)
{
	int	fd_infile;

	if (p.err_infile != 0 || p.err_in_cmd1 != 0)
		clean_up1_and_exit(p, pipefd[0], pipefd[1]);
	fd_infile = open(p.in_file, O_RDWR, 0644);
	if (fd_infile == -1)
	{
		clean_up2_and_exit(p, pipefd[0], pipefd[1]);
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_infile);
	}
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_infile);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_infile);
	if (execve(p.path_to_cmd1_executable, p.cmd1, NULL) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_infile);
	}
}

void	child_two(t_pipex p, int *pipefd)
{
	int	fd_outfile;

	if (p.err_outfile != 0 || p.err_in_cmd2 != 0)
		clean_up1_and_exit(p, pipefd[0], pipefd[1]);
	fd_outfile = open(p.out_file, O_WRONLY, 0644);
	if (fd_outfile == -1)
	{
		clean_up2_and_exit(p, pipefd[0], pipefd[1]);
	}
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_outfile);
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_outfile);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd_outfile);
	if (execve(p.path_to_cmd2_executable, p.cmd2, NULL) == -1)
	{
		clean_up3_and_exit(p, pipefd[0], pipefd[1], fd_outfile);
	}
}
