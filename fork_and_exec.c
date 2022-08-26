/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 10:19:18 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/26 17:10:22 by pskytta          ###   ########.fr       */
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
		ft_putendl(data->cmd);
		ft_putendl("Hello from the child process :)");
		if (execve(data->cmd, data->token, data->environ) == -1)
			ft_putendl("minishell: error with execve");
	}
	else if (pid_child < 0)
		ft_putendl(FORK_FAIL);
	else
	{
		pid_wait = waitpid(pid_child, &data->pid_status, 0);
		if (pid_wait == -1)
			ft_putendl(WAITPID_FAIL);
		ft_putendl("Parent is done waiting.");
		//free_double_ptr(arguments);
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

static int check_existense(t_shell *data)
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
			data->cmd = ft_strdup(temp);
			free(temp);
			return (TRUE);
		}
		ft_memset(temp, '\0', ft_strlen(temp));
		i++;
	}
	return(FALSE);
}

int	check_if_executable(t_shell *data)
{
	char	**arguments;
	int		i;
	int		ii;

	i = 1;
	ii = 0;
	arguments = (char **)malloc(sizeof(char *) * (data->token_count));
	if (arguments == NULL)
		exit(0);
	if (check_existense(data) == FALSE && data->cmd == NULL)
		return (exec_error_message(2, data->token[0]));
	else
	{
		create_child_process(data);
		return (TRUE);
	}


}
