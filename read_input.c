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

static char	*read_input_stdin(char *buf, int *quotes)
{
	char		*new;
	int			bytes_read;

	ft_memset(buf, 0, BUFFER);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read > 0 && bytes_read <= BUFFER)
		buf[bytes_read] = '\0';
	if (bytes_read > BUFFER)
		ft_putendl_fd(CMD_TOO_LONG, 2);
	if (simple_input_check(buf) == FALSE)
	{
		*quotes = TRUE;
		new = handle_quotes(buf);
		return (new);
	}
	else
	{
		buf[bytes_read - 1] = '\0';
		return (buf);
	}

}

static void	clear_and_free_buffer(char *string)
{
	ft_memset(string, 0, ft_strlen(string));
	ft_memdel((void *)&(string));
}

static int	exit_or_not(char *buf)
{
	if (ft_strequ(buf, EXIT) == TRUE)
	{
		create_or_append_history(buf);
		ft_memset(buf, 0, ft_strlen(buf));
		ft_memdel((void *)&(buf));
		ft_putendl(EXIT);
		return (FALSE);
	}
	else
		return (TRUE);
}

static int	is_empty(char *buf)
{
	int	i;
	int	ws;

	i = 0;
	ws = 0;
	if (ft_strequ(buf, NOSTRING) == TRUE)
		return (TRUE);
	while (buf[i] != '\0')
	{
		if (ft_is_wspace(buf[i]))
			ws++;
		i++;
	}
	if (ws == i)
	{
		create_or_append_history(buf);
		return (TRUE);
	}
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
		buf = (char *)ft_memalloc(BUFFER);
		buf = read_input_stdin(buf, &data->quotes);
		if (exit_or_not(buf) == FALSE)
			return (FALSE);
		if (is_empty(buf) == TRUE)
			clear_and_free_buffer(buf);
		else
		{
			parse_input(data, buf);
			if (ft_strequ(buf, "rm .minish_history") == 0)
				create_or_append_history(buf);
			clear_and_free_buffer(buf);
			if (data->token != NULL)
				ft_free_arr_of_arrays(data->token);
			ft_memdel((void *)&(data->cmd));
		}
		data->token_count = -1;
	}
}
