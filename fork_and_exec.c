/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/04 20:37:10 by pskytta          ###   ########.fr       */
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
			ft_putendl(EXECVE_ERROR);
		exit(EXIT_SUCCESS);
	}
	else if (pid_child < 0)
		ft_putendl(FORK_FAIL);
	else
	{
		pid_wait = waitpid(pid_child, &data->pid_status, 0);
		if (pid_wait == -1)
			ft_putendl(WAITPID_FAIL);
	}
}

static int	is_in_path(t_shell *data, int i)
{
	char	*temp;

	temp = NULL;
	while (data->split_path[i] != NULL)
	{
		temp = ft_strjoin(data->split_path[i], "/");
		temp = ft_strjoin(temp, data->token[0]);
		if (access(temp, F_OK) == 0)
		{
			data->cmd = ft_strdup(temp);
			free(temp);
			return (TRUE);
		}
		ft_memset(temp, '\0', ft_strlen(temp));
		i++;
	}
	return (FALSE);
}

static int	check_existance(t_shell *data)
{
	struct stat	info;
	char		*cd;

	cd = NULL;
	cd = ft_strjoin(getcwd(cd, 4096), "/");
	cd = ft_strjoin(cd, data->token[0]);
	if (lstat((const char *)cd, &info) == 0)
	{
		if (ft_is_directory(cd) == TRUE)
			return (3);
		data->cmd = ft_strdup(cd);
		free(cd);
		return (TRUE);
	}
	else if (lstat((const char *)cd, &info) == -1)
	{
		free(cd);
		return(2);
	}
	else
	{
		free(cd);
		return (FALSE);
	}
}

// MISSING: permission check
static int	verify_if_executable(t_shell *data)
{
	if (ft_strchr(data->token[0], '.') || ft_strchr(data->token[0], '/'))
		return (check_existance(data));
	else if (is_in_path(data, 0) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	initial_exec_checks(t_shell *data)
{
	int	check;

	check_expansion(data, 0);
	check = verify_if_executable(data);
	if (check == FALSE)
		return (exec_error_message(2, data->token[0]));
	else if (check == 2)
		return (exec_error_message(1, data->token[0]));
	else if (check == 3)
		return (exec_error_message(3, data->token[0]));
	else
	{
		create_child_process(data);
		return (TRUE);
	}
}
