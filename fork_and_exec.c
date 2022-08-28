/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/28 22:44:29 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	PATH is split already. Command line argument has been split into
**	different tokens.
*/
void	create_child_process(t_shell *data)
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

static int	exec_error_message(int id, char *name)
{
	if (id == 1)
	{
		ft_putstr(EXEC_NO_ACCESS);
		ft_putendl(name);
	}
	if (id == 2)
	{
		ft_putstr(CMD_NOT_FOUND);
		ft_putendl(name);
	}
	return (FALSE);
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

// MISSING: permission check
static int	verify_if_executable(t_shell *data)
{
	char	*cd;
	int		var_i;

	var_i = 0;
	cd = NULL;
	cd = ft_strjoin(getcwd(cd, 4096), "/");
	cd = ft_strjoin(cd, data->token[0]);
	if (access((const char *)cd, F_OK) == 0)
	{
		data->cmd = ft_strdup(cd);
		var_i = search_var_name("SHLVL", data);
		++data->environ[var_i][6];
		free(cd);
		return (TRUE);
	}
	else if (is_in_path(data, 0) == FALSE)
		return (FALSE);
	return (TRUE);

}

int	initial_exec_checks(t_shell *data)
{
	char	**arguments;

	check_expansion(data, 0);
	arguments = (char **)malloc(sizeof(char *) * (data->token_count));
	if (arguments == NULL)
		exit(1);
	if (verify_if_executable(data) == FALSE)
		return (exec_error_message(2, data->token[0]));
	else
	{
		create_child_process(data);
		return (TRUE);
	}
	free_double_ptr(arguments);
}
