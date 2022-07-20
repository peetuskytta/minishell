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
		buf[bytes_read - 1] = '\0';
	else
		ft_putendl(CMD_TOO_LONG);
}

static void	clear_and_free_buffer(char *string)
{
	ft_memset(string, '\0', ft_strlen(string));
	free(string);
}

static int	exit_and_clean(char *buf)
{
	if (ft_strequ(buf, EXIT) == true)
	{
		clear_and_free_buffer(buf);
		return (false);
	}
	else
		return (true);
}

static int	clear_or_env(t_shell *data, char *buf)
{
	int	i;

	i = 0;
	if (ft_strequ(buf, CLEAR) == true)
	{
		system("clear");
		return (true);
	}
	else if (ft_strequ(buf, ENV) == true)
	{
		while (data->environ[i] != NULL)
			ft_putendl(data->environ[i++]);
		return (true);
	}
	return (false);
}

int	command_prompt_loop(t_shell *data)
{
	char	*buf;

	while (true)
	{
		ft_putstr(PROMPT);
		buf = (char *)malloc(sizeof(char) * BUFFER);
		if (!buf)
			return (false);
		read_input_stdin(buf);
		if (exit_and_clean(buf) == false)
			return (false);
		if (clear_or_env(data, buf) == true)
			clear_and_free_buffer(buf);
		else
		{
			parse_input(data, buf);
			clear_and_free_buffer(buf);
		}
	}
}
