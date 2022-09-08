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

static void	read_input_stdin(t_shell *data, char *buf)
{
	int	bytes_read;

	ft_memset(buf, '\0', BUFFER);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read > 0 && bytes_read <= BUFFER)
		buf[bytes_read - 1] = '\0';
	if (bytes_read > BUFFER)
		ft_putendl(CMD_TOO_LONG);
	if (bytes_read > 1)
	{
		if (ft_strequ(data->history[data->h_index], buf) != 1)
		{
			data->h_index++;
			data->history[data->h_index] = ft_strdup(buf);
		}
	}
}

static void	clear_and_free_buffer(char *string)
{
	ft_memset(string, 0, ft_strlen(string));
	free(string);
}

static int	exit_or_not(char *buf)
{
	if (ft_strequ(buf, EXIT) == TRUE)
	{
		ft_memset(buf, 0, ft_strlen(buf));
		free(buf);
		ft_putendl("exit");
		return (FALSE);
	}
	else
		return (TRUE);
}

static int	is_empty(char *buf)
{
	if (ft_strequ(buf, NOSTRING) == TRUE)
		return (TRUE);
	return (FALSE);
}

int	command_prompt_loop(t_shell *data)
{
	char	*buf;

	while (TRUE)
	{
		ft_putstr(CYAN);
		ft_putstr(PROMPT);
		ft_putstr(DEFAULT);
		buf = (char *)malloc(sizeof(char) * BUFFER);
		if (!buf)
			return (FALSE);
		read_input_stdin(data, buf);
		if (exit_or_not(buf) == FALSE)
			return (FALSE);
		if (is_empty(buf) == TRUE)
			clear_and_free_buffer(buf);
		else
		{
			parse_input(data, buf);
			clear_and_free_buffer(buf);
			if (data->token != NULL)
				free_double_ptr(data->token);
		}
		data->token_count = -1;
	}
}
