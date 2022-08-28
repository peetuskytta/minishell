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
	ft_memset(string, 0, ft_strlen(string));
	free(string);
}

static int	exit_and_clean(char *buf)
{
	if (ft_strequ(buf, EXIT) == TRUE)
	{
		ft_memset(buf, 0, ft_strlen(buf));
		free(buf);
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
		read_input_stdin(buf);
		if (exit_and_clean(buf) == FALSE)
			return (FALSE);
		if (is_empty(buf) == TRUE)
			clear_and_free_buffer(buf);
		else
		{
			parse_input(data, buf);
			clear_and_free_buffer(buf);
		}
		data->token_count = -1;
	}
}
