/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_to_executable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:35:43 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/11 08:09:59 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	calc_number_of_paths_in_arr(char **paths)
{
	int	i;

	i = 0;
	if (paths == NULL || paths[i] == NULL)
	{
		return (0);
	}
	while (paths[i])
	{
		i++;
	}
	return (i);
}

static char	*make_potential_path_cmd(t_pipex *p, int *i, char *cmd)
{
	char	*path_with_slash;
	char	*path_with_slash_and_cmd;

	path_with_slash = ft_strjoin(p->paths[*i], "/");
	if (path_with_slash == NULL)
	{
		free_struct_pointer(p);
		exit(1);
	}
	path_with_slash_and_cmd = ft_strjoin(path_with_slash, cmd);
	if (path_with_slash_and_cmd == NULL)
	{
		free(path_with_slash);
		free_struct_pointer(p);
		exit(1);
	}
	free(path_with_slash);
	return (path_with_slash_and_cmd);
}

static char	*make_path_to_executable_cmd(t_pipex *p, char *cmd, int cmd_number)
{
	int		num_of_paths;
	int		i;
	char	*potential_path;

	num_of_paths = calc_number_of_paths_in_arr(p->paths);
	i = 0;
	while (i < num_of_paths)
	{
		potential_path = make_potential_path_cmd(p, &i, cmd);
		if (access(potential_path, F_OK) == 0)
		{
			if (access(potential_path, X_OK) == 0)
			{
				return (potential_path);
			}
		}
		free(potential_path);
		i++;
	}
	pipex_manual_err_msg_2("command not found", cmd, p);
	set_error_code_into_struct(p, cmd_number, 127);
	return (NULL);
}

static void	check_absolute_path_is_valid(t_pipex *p, char *path, int cmd_number)
{
	char	*command;

	if (cmd_number == 1)
		command = p->cmd1[0];
	if (cmd_number == 2)
		command = p->cmd2[0];
	if (*path == '.')
	{
		pipex_manual_err_msg_2("permission denied", command, p);
		set_error_code_into_struct(p, cmd_number, 126);
		return ;
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			return ;
		}
	}
	pipex_err_msg(path, p);
	set_error_code_into_struct(p, cmd_number, 126);
}

char	*find_path_to_executable(t_pipex *p, char *cmd, int cmd_number)
{
	char	*path_to_executable;

	if (ft_strchr(&cmd[0], '/') != NULL)
	{
		check_absolute_path_is_valid(p, cmd, cmd_number);
		path_to_executable = ft_strdup(cmd);
		if (path_to_executable == NULL)
		{
			free_struct_pointer(p);
			exit (1);
		}
	}
	else
	{
		path_to_executable = make_path_to_executable_cmd(p, cmd, cmd_number);
	}
	return (path_to_executable);
}
