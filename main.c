/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:05:01 by mkorpela          #+#    #+#             */
/*   Updated: 2024/05/16 12:34:11 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_only_4_arguments(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Pass in exactly 4 args\n", 2);
		exit (1);
	}
}

static void	free_struct_perror_and_exit_with_errno(t_pipex p, char *perror_msg)
{
	free_struct(p);
	perror(perror_msg);
	exit (errno);
}

static int	waitpid_and_clean(t_pipex p, int pid_c1, int pid_c2, int pipefd_out)
{
	close(pipefd_out);
	if (waitpid(pid_c1, NULL, 0) == -1)
	{
		free_struct(p);
		perror("waitpid - child 1");
		exit (errno);
	}
	if (waitpid(pid_c2, NULL, 0) == -1)
	{
		free_struct(p);
		perror("waitpid - child 2");
		exit (errno);
	}
	if (p.err_outfile != 0)
	{
		free_struct(p);
		exit (p.err_outfile);
	}
	if (p.err_in_cmd2 != 0)
	{
		free_struct(p);
		exit (p.err_in_cmd2);
	}
	free_struct(p);
	// while(42)
	// {
		
	// }
	exit (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	p;
	int		pipefd[2];
	int		pid_child1;
	int		pid_child2;

	p = (t_pipex){};
	check_only_4_arguments(argc);
	p = initialize_struct(p, argv, envp);
	if (pipe(pipefd) == -1)
		free_struct_perror_and_exit_with_errno(p, "pipe");
	pid_child1 = fork();
	if (pid_child1 == -1)
		free_struct_perror_and_exit_with_errno(p, "fork 1");
	if (pid_child1 == 0)
		child_one(p, pipefd);
	pid_child2 = fork();
	if (pid_child1 == -1)
		free_struct_perror_and_exit_with_errno(p, "fork 2");
	if (pid_child2 == 0)
		child_two(p, pipefd);
	else
	{
	// 	while(42)
	// {
		
	// }
		close(pipefd[0]);
		waitpid_and_clean(p, pid_child1, pid_child2, pipefd[1]);
	}
}
