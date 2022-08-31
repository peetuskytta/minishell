/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec_auxiliary.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:21:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/31 11:23:02 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_shell(t_shell *data)
{
	if (ft_strequ(data->token[0], "bash") == 1)
		modify_env(data, "SHELL", data->cmd, 0);
	if (ft_strequ(data->token[0], "zsh") == 1)
		modify_env(data, "SHELL", data->cmd, 0);
	if (ft_strequ(data->token[0], "minishell") == 1)
		modify_env(data, "SHELL", data->cmd, 0);
}

int	exec_error_message(int id, char *name)
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
