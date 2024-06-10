/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_syntax.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 12:14:08 by mkorpela          #+#    #+#             */
/*   Updated: 2024/04/10 12:17:46 by mkorpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	is_command_an_empty_string(char *argv, t_pipex p)
{
	if (argv[0] == '\0')
	{
		pipex_manual_err_msg("permission denied", NULL, p);
		return (true);
	}
	return (false);
}

static bool	is_there_a_space_before_the_command(char *argv, t_pipex p)
{
	if (argv[0] == ' ')
	{
		pipex_manual_err_msg("command not found", argv, p);
		return (true);
	}
	return (false);
}

static bool	is_there_only_space_after_the_command(char *argv, t_pipex p)
{
	int	i;
	int	whitespace_counter;

	i = 0;
	while (argv[i] == ' ')
	{
		i++;
	}
	while (argv[i] >= 33 && argv[i] <= 126)
	{
		i++;
	}
	whitespace_counter = 0;
	while (argv[i] == ' ')
	{
		whitespace_counter++;
		i++;
	}
	if (argv[i] == '\0' && whitespace_counter > 0)
	{
		pipex_manual_err_msg("command not found", argv, p);
		return (true);
	}
	return (false);
}

static int	is_there_only_space_in_command(char *argv, t_pipex p)
{
	int	i;

	i = 0;
	while (argv[i] == ' ')
	{
		i++;
	}
	if (argv[i] == '\0')
	{
		pipex_manual_err_msg("command not found", argv, p);
		return (1);
	}
	return (0);
}

int	check_command_syntax(char *argv, t_pipex p)
{
	if (is_command_an_empty_string(argv, p) == true)
	{
		return (1);
	}
	if (is_there_only_space_in_command(argv, p) == true)
	{
		return (1);
	}
	if (is_there_a_space_before_the_command(argv, p) == true)
	{
		return (1);
	}
	if (is_there_only_space_after_the_command(argv, p) == true)
	{
		return (1);
	}
	return (0);
}
