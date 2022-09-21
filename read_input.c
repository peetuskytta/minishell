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
static int	is_s_quote(char c)
{
	return (c == SINGLEQUOTE);
}

static int	is_d_quote(char c)
{
	return (c == DOUBLEQUOTE);
}
*/

static int	is_oddnbr(int nbr)
{
	if (nbr % 2 != 0)
		return (TRUE);
	return (FALSE);
}

static int	count_chars_in_str(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i++] == c)
			count++;
	}
	return (count);
}

static void	read_until_quote(char c, char *new)
{
	char	*extra;
	int		bytes_read;

	bytes_read = 0;
	extra = (char *)ft_memalloc(BUFFER);
	ft_memset(extra, '\0', BUFFER);
	while (TRUE)
	{
		if (c == SINGLEQUOTE)
			ft_putstr_fd(S_QUOTE, 1);
		if (c == DOUBLEQUOTE)
			ft_putstr_fd(D_QUOTE, 1);
		bytes_read = read(0, extra, BUFFER);
		if (bytes_read > 0 && bytes_read <= BUFFER)
			extra[bytes_read] = '\0';
		ft_strcat(new, extra);
		if (ft_strrchr(extra, c))
		{
			bytes_read = ft_strrchr(extra, c) - extra;
			if (extra[bytes_read - 1] == BACKSLASH)
			{
					if (is_oddnbr(count_chars_in_str(new, BACKSLASH)) == FALSE)
						ft_putnbr_endl(count_chars_in_str(extra, BACKSLASH));
					ft_memdel((void *)&(extra));
					break ;
			}
		}
		ft_memset(extra, '\0', BUFFER);
	}
	new[ft_strlen(new)] = '\0';
}

static void	check_quotes_amount(char *new, char *old)
{
	int		sq;
	int		dq;
	char	c;

	sq = count_chars_in_str(old, SINGLEQUOTE);
	dq = count_chars_in_str(old, DOUBLEQUOTE);
	if (is_oddnbr(sq) || is_oddnbr(dq))
	{
		if (is_oddnbr(sq))
			c = SINGLEQUOTE;
		else if (is_oddnbr(dq))
			c = DOUBLEQUOTE;
		ft_strcpy(new, old);
		read_until_quote(c, new);
	}
}

static char	*handle_quotes(char *old/*, int i*/)
{
	char	*new;

	new = ft_strnew(ft_strlen(old) + 4096);
	ft_memset(new, '\0', ft_strlen(new));
	check_quotes_amount(new, old);
/*	while (old[i] != '\0')
	{
		if (is_s_quote(old[i]) == TRUE)
		{
			*new = old[++i];
			while (old[i] != '\0')
			{
				if (is_s_quote(old[i]) == FALSE)
					*new = old[i++];
				else if (is_s_quote(old[i]) == TRUE)
			}
		}
		if (is_d_quote(old[i]) == TRUE)
		{
			*new = old[++i];
			while (is_d_quote(old[i]) == FALSE)
				*new++ = old[i++];
		}
		*new++ = old[i++];
	}
*/
	return (new);
}

static void	read_input_stdin(char *buf)
{
	char		*new;
	int			bytes_read;

	ft_memset(buf, 0, BUFFER);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read > 0 && bytes_read <= BUFFER)
		buf[bytes_read] = '\0';
	if (bytes_read > BUFFER)
		ft_putendl(CMD_TOO_LONG);
	if (simple_input_check(buf) == FALSE)
	{
		new = handle_quotes(buf/*, 0*/);
		ft_putstr(new);
		int count = 0;
		while (*new++ !='\0')
		{
			if (*new == '\n')
				count++;
		}
		ft_putstr_fd("number of \\n: ", 1);
		ft_putnbr_endl(count);
		exit(1);
	}
	else
		buf[bytes_read] = '\0';

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
		ft_putendl("exit");
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
		read_input_stdin(buf);
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
