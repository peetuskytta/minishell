/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 21:18:50 by pskytta          ###   ########.fr       */
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

static int	is_in_path(t_shell *data)
{
	char	temp[4096];

	ft_memset(temp, '\0', 4096);
	if (!ft_strchr(data->token[0], '/'))
	{
		if (loop_path_variable(data, temp, 0) == TRUE)
			return (TRUE);
	}
	if (ft_strchr(data->token[0], '/'))
	{
		data->cmd = ft_strdup(data->token[0]);
		return (TRUE);
	}
	return (FALSE);
}

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

static int	verify_if_executable(t_shell *data)
{
	if (data->token[0][0] == '.' || data->token[0][0] == '/')
	{
		if (ft_strequ(data->token[0], ".") == 1)
			return (4);
		return (check_existence(data));
	}
	if (search_var_name("PATH", data) < 0)
		return (FALSE);
	else if (is_in_path(data) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	initial_exec_checks(t_shell *data)
{
	int	check;

	if (ft_strequ(data->token[0], CD) == 1)
		return (current_dir_actions(data));
	ft_memdel((void *)&(data->pwd));
	check = verify_if_executable(data);
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
