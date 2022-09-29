/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/29 21:35:01 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	PATH is split already. Command line argument has been split into
**	different tokens.
*/
static void	create_child_process(t_shell *data)
{
	pid_t	pid_child;
	pid_t	pid_wait;

	pid_child = fork();
	if (pid_child == 0)
	{
		if (execve(data->cmd, data->token, data->environ) == -1)
			ft_putendl_fd(EXECVE_ERROR, 2);
		ft_memdel((void *)&(data->cmd));
		exit(EXIT_SUCCESS);
	}
	else if (pid_child < 0)
		ft_putendl_fd(FORK_FAIL, 2);
	else
	{
		pid_wait = waitpid(pid_child, &data->pid_status, 0);
		if (pid_wait == -1)
			ft_putendl_fd(WAITPID_FAIL, 2);
	}
}

static int	is_in_path(t_shell *data, int i)
{
	char	temp[4096];

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

static int	check_existence(t_shell *data)
{
	struct stat	info;
	char		cd[4096];

	ft_memset(cd, '\0', 4096);
	if (data->token[0][0] != '/')
		ft_strcat(getcwd(cd, 4096), "/");
	ft_strcat(cd, data->token[0]);
	if (lstat((const char *)cd, &info) == 0)
	{
		if (ft_is_directory(cd) == TRUE)
			return (3);
		data->cmd = ft_strdup(cd);
		return (TRUE);
	}
	else if (lstat((const char *)cd, &info) == -1)
		return (2);
	else
		return (FALSE);
}

// MISSING: permission check
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

int	initial_exec_checks(t_shell *data)
{
	int	check;

	if (ft_strequ(data->token[0], CD) == 1)
		return (current_dir_actions(data));
	check = verify_if_executable(data);
	if (check == FALSE)
		return (exec_error_message(2, data->token[0]));
	else if (check == 2)
		return (exec_error_message(1, data->token[0]));
	else if (check == 3)
		return (exec_error_message(3, data->token[0]));
	else if (check == 4)
		return (exec_error_message(4, data->token[0]));
	else if (check == 5)
		return (exec_error_message(5, data->token[0]));
	else
	{
		modify_env(data, "_", data->token[0], 0);
		if (ft_strlen(data->token[0]) > 0)
			create_child_process(data);
		ft_memdel((void *)&(data->cmd));
		return (TRUE);
	}
}
