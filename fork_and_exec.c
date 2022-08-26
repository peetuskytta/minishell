/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/26 16:04:42 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* PATH is split already. Command line argument has been split into different tokens. */
void	create_child_process(t_shell *data)
{
	pid_t	pid_child;
	pid_t	pid_wait;

	pid_child = fork();
	if (pid_child == 0)
	{
		process_child(data);
		ft_putendl("Hello from the child process :)");

		// check for permission
		// add tokens together separated by spaces
		// use the tokens in execve
	}
	else if (pid_child < 0)
		ft_putendl(FORK_FAIL);
	else
	{
		pid_wait = waitpid(pid_child, &data->pid_status, 0);
		if (pid_wait == -1)
			ft_putendl(WAITPID_FAIL);
		ft_putendl("Parent is done waiting.");
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
	return (TRUE);
}

static int check_if_exists(t_shell *data)
{
	char	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (data->split_path[i] != NULL)
	{
		temp = ft_strjoin(data->split_path[i], "/");
		temp = ft_strjoin(temp, data->token[0]);
		//check permissions before F_OK if (permission_ok) == FALSE, return(FALSE)
		if (access(temp, F_OK) == 0)
		{
			data->cmd = temp;
			return (TRUE);
		}
		ft_memset(temp, '\0', ft_strlen(temp));
		i++;
	}
	return(FALSE);
}

int	check_if_executable(t_shell *data)
{
	if (check_existence(data) == FALSE && data->cmd == NULL)
		return (exec_error_message(2, data->token[0]));
	else
		create_child_process(data);


}
