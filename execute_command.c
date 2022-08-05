/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:15:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/20 11:15:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_builtin(t_shell *data)
{
	if (ft_strequ(data->token[0], CD))
	{
		ft_putendl("function pointer to CD");
		return (TRUE);
	}
	else if (ft_strequ(data->token[0], ECHO))
	{
		ft_putendl("function pointer to ECHO");
		return (TRUE);
	}
	else if (ft_strequ(data->token[0], SETENV))
		return (change_environ(data, 1));
	else if (ft_strequ(data->token[0], UNSETENV))
		return (change_environ(data, 2));
	else if (ft_strequ(data->token[0], ENV))
		return (output_environment(data, 0));
	return (FALSE);
}

void	execute_command(t_shell *data)
{
	if (check_if_builtin(data) == FALSE)
		reset_last_cmd_env(data, data->last_cmd);
}
