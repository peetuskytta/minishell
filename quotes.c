/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 13:29:22 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	writes "dquote>" for open double quote and "quote>" for open single quote
*/
static void	write_open_quote(char c)
{
	if (c == S_QUOTE)
		ft_putstr_fd(S_QUOTE_ARROW, 1);
	if (c == D_QUOTE)
		ft_putstr_fd(D_QUOTE_ARROW, 1);
}

/*
**	Reads new input to *extra and joines the new & extra. Checks if quotes
**	are closed or not and repeats the above if necessary.
*/
static char	*read_until_quote(char c, char *old, int bytes_read, int num_quotes)
{
	char	*new;
	char	*extra;

	new = ft_strdup(old);
	while (TRUE)
	{
		write_open_quote(c);
		extra = (char *)ft_memalloc(BUFFER);
		bytes_read = read(0, extra, BUFFER);
		if (bytes_read < BUFFER)
		{
			new = strjoin_free(new, extra);
			num_quotes = ft_chrstr(new, c);
			if (ft_is_oddnbr(num_quotes) == FALSE)
				break ;
		}
		else
			break ;
	}
	return (new);
}

/*
**	Returns the char value of the quote that is open.
*/
static char	identify_open_quote(char *old, char c, int *quote)
{
	if (ft_is_oddnbr(quote[0]) && ft_is_oddnbr(quote[1]))
	{
		if (ft_strrchr(old, S_QUOTE))
			c = D_QUOTE;
		else
			c = S_QUOTE;
		return (c);
	}
	else if (ft_is_oddnbr(quote[0]))
		c = S_QUOTE;
	else if (ft_is_oddnbr(quote[1]))
		c = D_QUOTE;
	return (c);
}

/*
**	Quote handling "driver function" which identifies the open quote
**	and moves to read until new quote is found.
*/
char	*handle_open_quotes(t_shell *data, char *old, int *quotes)
{
	char	*new;
	char	c;

	c = '\0';
	c = identify_open_quote(old, c, quotes);
	data->quotes = TRUE;
	new = read_until_quote(c, old, 0, 0);
	data->input_len = ft_strlen(new);
	if (data->input_len >= 4096)
	{
		ft_putstr_fd("\e[1;37m", STDERR_FILENO);
		error_print(MINISH, "... seriosly? ", CMD_TOO_LONG);
		ft_putstr_fd(" \033[0m", STDERR_FILENO);
		ft_memset(new, '\0', data->input_len);
		data->input_len = -1;
		return (new);
	}
	return (new);
}
