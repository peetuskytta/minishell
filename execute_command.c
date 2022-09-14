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

static int	output_history(t_shell *data, int i)
{
	if (data->history[0] == NULL)
		ft_putendl("minishell: no history.");
	/*else if (ft_strequ(data->token[0], "!!") == TRUE)
	{
		ft_memdel((void *)&data->token[0]);
		data->token[0] = ft_strdup(data->history[last_history_index(data)]);
		//initial_exec_checks(data);
	}*/
	else if (ft_strequ(data->token[0],"history") == TRUE)
	{
		while (data->history[i] != NULL)
		{
			ft_putnbr(i);
			ft_putstr("  ");
			ft_putendl(data->history[i++]);
		}
	}
	return (TRUE);
}

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
	else if (ft_strequ(data->token[0], HISTORY) ||
		data->token[0][0] == '!')
		return (output_history(data, 1));
	return (FALSE);
}

/*void	handle_command(t_shell *data)
{
	if (check_if_builtin(data) == FALSE)
		reset_last_cmd_env(data, data->last_cmd);
	else
	{
		create_child_process(data);
		// set data->last_cmd to be the path+binary executed succesfully
		reset_last_cmd_env(data, data->last_cmd);
	}
}*/
