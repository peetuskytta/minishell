/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:07:16 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/15 13:07:16 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_input_stdin(char *buf)
{
	int	bytes_read;

	ft_memset(buf, '\0', BUFFER);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read > 0 && bytes_read <= BUFFER)
	{
		buf[bytes_read - 1] = '\0';
	}
	else
		ft_putendl(CMD_TOO_LONG);
}

static void	clear_and_free(char *string)
{
	ft_memset(string, '\0', ft_strlen(string));
	free(string);
}

static int	exit_or_clear(t_shell *data, char *buf)
{
	ft_putendl_fd(data->environ_n[3], 0);
	if (ft_strequ(buf, CLEAR) == true)
		system("clear");
	else if (ft_strequ(buf, EXIT) == true)
	{
		clear_and_free(buf);
		return (false);
	}
	return (true);
}

int	command_prompt_loop(t_shell *data)
{
	char	*buf;

	ft_putendl_fd(data->environ_n[3], 0);
	while (true)
	{
		ft_putstr(PROMPT);
		buf = (char *)malloc(sizeof(char) * BUFFER);
		read_input_stdin(buf);
		if (exit_or_clear(data, buf) == false)
			return (false);
		// else
		//	parse_input(&data, buf);
		// act_on_command();
		// the two lines below are just for visualizing what is in buf
		if (buf[0] != '\0')
			ft_putendl(buf);
		clear_and_free(buf);
	}
}
