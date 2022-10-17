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

/*
**	Funtion handles which action to take when history command is used
*/
static int	history_driver(t_shell *data)
{
	int	fd;

	if (ft_strequ(HISTORY, data->token[0]) == 1)
	{
		if (ft_strequ(data->token[1], "-c") == 1)
		{
			fd = open(SH_HISTORY, O_RDWR | O_TRUNC);
			if (fd > 0)
				close(fd);
		}
		else
			handle_history(1);
		return (TRUE);
	}
	return (FALSE);
}

/*
**	This function outputs the whole history to the stdout line by line.
*/
void	output_history(int i, int fd)
{
	char	*line;

	line = NULL;
	if (fd > 0)
	{
		while (get_next_line(fd, &line) == 1)
		{
			ft_putnbr(i++);
			ft_putstr("  ");
			ft_putendl(line);
			ft_memdel((void *)&(line));
		}
		close(fd);
	}
	else
		ft_putendl_fd("minishell: No history.", 2);
}

/*
**	Checks and executes the builtin. If command (data->token[0])
**	is not builtin the function returns FALSE.
*/
int	check_if_builtin(t_shell *data)
{
	if (ft_strequ(data->token[0], CD)
		|| ft_strequ(data->token[0], "CD"))
		return (current_dir_actions(data));
	else if (ft_strequ(data->token[0], ECHO)
		|| ft_strequ(data->token[0], "ECHO"))
		return (echo_driver(data, 0));
	else if (ft_strequ(data->token[0], SETENV)
		|| ft_strequ(data->token[0], "SETENV"))
		return (change_environ(data, 1));
	else if (ft_strequ(data->token[0], UNSETENV)
		|| ft_strequ(data->token[0], "UNSETENV"))
		return (change_environ(data, 2));
	else if (ft_strequ(data->token[0], ENV)
		|| ft_strequ(data->token[0], "ENV"))
		return (handle_env(data, 0));
	else if (ft_strequ(data->token[0], HISTORY)
		|| ft_strequ(data->token[0], "!!")
		|| ft_strequ(data->token[0], "HISTORY"))
		return (history_driver(data));
	return (FALSE);
}
