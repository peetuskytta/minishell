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

/*
**	Reads the stdin for input and moves to handle quotes if there is odd
**	number of either of the quotes.
*/
static char	*read_input_stdin(t_shell *data, char *buf, int bytes_read)
{
	char		*new;
	int			quotes[2];

	ft_memset(buf, 0, BUFFER + 1);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read < BUFFER + 1 && simple_input_check(buf) == FALSE)
	{
		data->quotes = TRUE;
		if (odd_nbr_of_quotes(buf, quotes) == FALSE)
		{
			buf[bytes_read - 1] = '\0';
			return (buf);
		}
		new = handle_open_quotes(data, buf, quotes);
		if (data->input_len == -1)
			data->quotes = FALSE;
		ft_memdel((void *)&(buf));
		return (new);
	}
	buf[bytes_read - 1] = '\0';
	return (buf);
}

static void	clear_and_free_buffer(char *string)
{
	ft_memset(string, 0, ft_strlen(string));
	ft_memdel((void *)&(string));
}

/*
**	Handles empty or NULL string input and jumps the whitespaces.
*/
static int	is_empty(char *buf)
{
	int	i;
	int	ws;

	i = 0;
	ws = 0;
	if (ft_strequ(buf, NO_STRING) == TRUE || buf == NULL)
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

/*
**	This loop only stops when "exit" is written to the STDIN.
*/
int	command_prompt_loop(t_shell *data)
{
	char	*buf;

	while (TRUE)
	{
		write_prompt_and_folder(data);
		buf = (char *)ft_memalloc(BUFFER + 1);
		buf = read_input_stdin(data, buf, 0);
		if (is_empty(buf) == TRUE || data->input_len == -1)
			clear_and_free_buffer(buf);
		else
		{
			if (parse_input(data, buf) == FALSE)
				return (FALSE);
			if (ft_strequ(buf, "rm .minish_history") == 0)
				create_or_append_history(buf);
			clear_and_free_buffer(buf);
			if (data->token != NULL)
				free_array(data->token);
			ft_memdel((void *)&(data->cmd));
		}
		data->input_len = 0;
		data->token_count = -1;
	}
}
