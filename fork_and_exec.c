/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/12 10:10:35 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function forks the process and executes a binary. Waits for it to be
**	ready and returns control to the parent process (minishell).
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

/*
**	Checks if the given argument has '/' or not and proceeds
**	to check if it is an executable or copies the same to data->cmd
**	in case '/' is found.
*/
static int	is_in_path(t_shell *data)
{
	char	temp[4096];

	if (data->input_len > 4095)
		return (FALSE);
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

/*
**	Verification for existence with lstat() and proceeds to
**	test if it is a directory. In case TRUE return 3 triggering
**	error message later.
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
**	First checks if the argument is an executable found in the current
**	folder. Otherwise move on to check if it's in PATH variable.
*/
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

/*
**	Executable verification process starts here and moves
**	to create a child process if all the checks are OK.
*/
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
