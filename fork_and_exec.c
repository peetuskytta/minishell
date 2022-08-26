/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/26 13:29:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prepare_exec(t_shell *data)
{
	char	*temp;
	int		i;

	i = 0;
	while (data->split_path[i] != NULL)
	{
		temp = ft_strdup(data->split_path[i]);
		ft_strcat(temp, "/");
		ft_strcat(temp, data->token[0]);
		ft_putendl(temp);
		//check permissions before F_OK
		if (access(temp, F_OK) == 0)
			data->cmd = temp;
		ft_memset(temp, '\0', ft_strlen(temp));
		i++;
	}
}

/* PATH is split already. Command line argument has been split into different tokens. */
void	create_child_process(t_shell *data)
{
	pid_t	pid_child;
	pid_t	pid_wait;

	pid_child = fork();
	if (pid_child == 0)
	{
		ft_putendl("Hello from the child process :)");

		prepare_exec(data);
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
