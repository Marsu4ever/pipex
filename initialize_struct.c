/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:24:24 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/11 08:24:55 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_pipex	check_infile_permissions(t_pipex p)
{
	if (access(p.in_file, F_OK) == -1)
	{
		pipex_manual_err_msg("no such file or directory", p.in_file, p);
		p.err_infile = 1;
		return (p);
	}
	if (access(p.in_file, R_OK) == -1)
	{
		pipex_manual_err_msg("permission denied", p.in_file, p);
		p.err_infile = 1;
		return (p);
	}
	return (p);
}

static t_pipex	check_and_make_first_pair_of_args(char *argv, t_pipex p)
{
	p = check_infile_permissions(p);
	if (p.err_infile == 1)
	{
		return (p);
	}
	if (check_command_syntax(argv, p) == 1)
	{
		p.err_in_cmd1 = 1;
		return (p);
	}
	p.cmd1 = ft_split(argv, ' ');
	if (p.cmd1 == NULL)
	{
		free_struct(p);
		exit (1);
	}
	p.path_to_cmd1_executable = find_path_to_executable(&p, p.cmd1[0], 1);
	return (p);
}

static t_pipex	make_outfile_if_no_exist_and_check_permissions(t_pipex p)
{
	int	fd_temp;

	if (access(p.out_file, F_OK) == -1)
	{
		fd_temp = open(p.out_file, O_CREAT, 0644);
		if (fd_temp == -1)
		{
			free_struct_and_error_msg(p, "open func - if outfile no exist\n");
			exit(errno);
		}
		close(fd_temp);
	}
	if (access(p.out_file, W_OK) == -1)
	{
		pipex_manual_err_msg("permission denied", p.out_file, p);
		p.err_outfile = 1;
		return (p);
	}
	return (p);
}

static t_pipex	check_and_make_second_pair_of_args(char *argv, t_pipex p)
{
	p = make_outfile_if_no_exist_and_check_permissions(p);
	if (check_command_syntax(argv, p) == 1)
	{
		p.err_in_cmd2 = 1;
		return (p);
	}
	p.cmd2 = ft_split(argv, ' ');
	if (p.cmd2 == NULL)
	{
		free_struct(p);
		exit (1);
	}
	p.path_to_cmd2_executable = find_path_to_executable(&p, p.cmd2[0], 2);
	return (p);
}

t_pipex	initialize_struct(t_pipex p, char **argv, char **envp)
{
	p.envp = envp;
	p.paths = find_paths_to_executables(p);
	p.in_file = argv[1];
	p = check_and_make_first_pair_of_args(argv[2], p);
	p.out_file = argv[4];
	p = check_and_make_second_pair_of_args(argv[3], p);
	return (p);
}
