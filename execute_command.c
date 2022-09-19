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

static int	handle_exclamation(t_shell *data)
{
	int		i;
	char	temp[4096];

	i = 0;
	ft_memset(temp, 0, 4096);
	handle_history(data, 2);
	if (ft_strequ(HISTORY, data->token[0]) == 1 && data->token[1] == NULL)
	{
		handle_history(data, 1);
		create_or_append_history(data->token[0]);
		return (TRUE);
	}
	if (data->token[1] != NULL)
	{
		ft_strcat(temp, data->token[i++]);
		while (data->token[i] != NULL)
		{
			ft_strcat(temp, " ");
			ft_strcat(temp, data->token[i++]);
		}
		create_or_append_history(temp);
		ft_memset(temp, 0, 4096);
	}
	return (FALSE);
}

static int	history_driver(t_shell *data)
{
	int	fd;

	if (ft_strequ(HISTORY, data->token[0]) == 1)
	{
		if (ft_strequ(data->token[1], "-c") == 1)
		{
			fd = open(SH_HISTORY, O_RDWR | O_TRUNC);
			close(fd);
		}
		else
			handle_history(data, 1);
		return (TRUE);
	}
	else if (ft_strequ("!!", data->token[0]) == 1 && data->token[1] == NULL)
		return (handle_exclamation(data));
	else if (data->token[0][0] == '!' && ft_isdigit(data->token[0][1]))
		handle_history(data, 3);
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
	}
	else
		ft_putendl("minishell: No history.");
	close(fd);
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
