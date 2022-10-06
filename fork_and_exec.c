/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/06 17:27:36 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	PATH is split already. Command line argument has been split into
**	different tokens.
*/
void	create_child_process(t_shell *data, char **env)
{
	pid_t	pid_child;
	pid_t	pid_wait;

	pid_child = fork();
	if (pid_child == 0)
	{
		if (execve(data->cmd, data->token, env) == -1)
			ft_putendl_fd(EXECVE_ERROR, STDERR_FILENO);
		ft_memdel((void *)&(data->cmd));
		exit(EXIT_SUCCESS);
	}
	else if (pid_child < 0)
		ft_putendl_fd(FORK_FAIL, STDERR_FILENO);
	else
	{
		pid_wait = waitpid(pid_child, &data->pid_status, 0);
		if (pid_wait == -1)
			ft_putendl_fd(WAITPID_FAIL, STDERR_FILENO);
	}
}

/*
**	If PATH environment variable exists it is split and the result is used to
**	test if the token is in one of the folders indicated by the PATH.
*/
static int	is_in_path(t_shell *data, int i)
{
	char	temp[4096];

	if (search_var_name("PATH", data) < 0)
		return (FALSE);
	split_path_variable(data, 0);
	ft_memset(temp, '\0', 4096);
	if (!(ft_strchr(data->token[0], '/')))
	{
		if (loop_path_variable(data, temp, 0) == TRUE)
			return (TRUE);
	}
	if (ft_strchr(data->token[0], '/'))
	{
		while (data->split_path[i] != NULL)
		{
			if (ft_strequ(data->split_path[i], data->token[0]) == 1)
			{
				data->cmd = ft_strdup(data->token[0]);
				return (TRUE);
			}
			i++;
		}
	}
	return (FALSE);
}

/*
**	Checks if the given token[0] is a valid file and not a directory.
*/
static int	check_existence(t_shell *data)
{
	struct stat	info;

	if (lstat((const char *)data->token[0], &info) == 0)
	{
		if (ft_is_directory(data->token[0]) == TRUE)
			return (3);
		data->cmd = ft_strdup(data->token[0]);
		return (TRUE);
	}
	else if (data->token[0][0] == '.' && data->token[0][1] == '/')
		return (5);
	else
		return (FALSE);
}

/*
**	This function directs the verification of a potential binary file before execution.
*/
static int	verify_if_executable(t_shell *data)
{
	if (data->token[0][0] == '.' || data->token[0][0] == '/')
	{
		if (ft_strequ(data->token[0], ".") == 1)
			return (4);
		return (check_existence(data));
	}
	else if (is_in_path(data, 0) == FALSE)
		return (FALSE);
	return (TRUE);
}

/*
**	Function handles the token[0] verification process before it is passed
**	to the create_child_process function.
*/
int	initial_exec_checks(t_shell *data)
{
	int	check;

	if (ft_strequ(data->token[0], CD) == 1)
		return (current_dir_actions(data));
	check = verify_if_executable(data);
	if (data->split_path == NULL)
		ft_free_arr_of_arrays(data->split_path);
	ft_memdel((void *)&(data->pwd));
	if (exec_error_check(data, check) != 1)
		return (FALSE);
	else
	{
		modify_env(data, "_", data->token[0], 0);
		if (ft_strlen(data->token[0]) > 0)
			create_child_process(data, data->environ);
		ft_memdel((void *)&(data->cmd));
		return (TRUE);
	}
}
