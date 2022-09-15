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

static int	output_environment(t_shell *data, int i)
{
	if (data->token_count == 0)
	{
		reset_last_cmd_env(data, data->last_cmd);
		while (data->env_count > i)
			ft_putendl(data->environ[i++]);
		return (TRUE);
	}
	else
	{
		reset_last_cmd_env(data, data->last_cmd);
		return (TRUE);
	}
}

static int	history_driver(t_shell *data)
{
	if (ft_strequ(HISTORY, data->token[0]) == 1)
		handle_history(data, 1);
	else if (ft_strequ("!!", data->token[0]) == 1)
		handle_history(data, 2);
	else if (data->token[0][0] == '!' && ft_isdigit(data->token[0][1]))
		handle_history(data, 3);
	return (TRUE);
}

int	check_if_builtin(t_shell *data)
{
	if (ft_strequ(data->token[0], CD))
		return (current_dir_actions(data));
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
	else if (ft_strequ(data->token[0], HISTORY) || data->token[0][0] == '!')
		return (history_driver(data));
	return (FALSE);
}
