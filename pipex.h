/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 12:07:09 by mkorpela          #+#    #+#             */
/*   Updated: 2024/05/20 10:24:23 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <sys/errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>

typedef struct s_pipex
{
	char	*in_file;
	char	**cmd1;
	char	**cmd2;
	char	*out_file;
	char	*path_to_cmd1_executable;
	char	*path_to_cmd2_executable;
	char	**envp;
	char	**paths;
	int		err_infile;
	int		err_outfile;
	int		err_in_cmd1;
	int		err_in_cmd2;
}	t_pipex;

int		check_command_syntax(char *argv, t_pipex p);
void	child_one(t_pipex p, int *pipefd);
void	child_two(t_pipex p, int *pipefd);
char	*find_path_to_executable(t_pipex *p, char *cmd, int cmd_number);
char	**find_paths_to_executables(t_pipex p);
void	free_struct(t_pipex p);
void	free_struct_and_error_msg(t_pipex p, char *error_msg);
void	free_struct_and_exit_with_errno(t_pipex p);
void	free_struct_pointer_and_exit_with_errno(t_pipex *p);
void	free_struct_pointer(t_pipex *p);
t_pipex	initialize_struct(t_pipex p, char **argv, char **envp);
void	pipex_err_msg(char *where_err_msg, t_pipex *p);
void	pipex_manual_err_msg(char *err_msg, char *where, t_pipex p);
void	pipex_manual_err_msg_2(char *err_msg, char *where, t_pipex *p);
void	set_error_code_into_struct(t_pipex *p, int cmd_number, int error_code);

#endif