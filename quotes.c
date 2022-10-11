/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/11 14:01:38 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_open_quote(char c)
{
	if (c == S_QUOTE)
		ft_putstr_fd(S_QUOTE_ARROW, 1);
	if (c == D_QUOTE)
		ft_putstr_fd(D_QUOTE_ARROW, 1);
}

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
		if (bytes_read <= BUFFER - 1)
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

int	odd_nbr_of_quotes(char *buf, int *quotes)
{
	quotes[0] = ft_chrstr(buf, S_QUOTE);
	quotes[1] = ft_chrstr(buf, D_QUOTE);
	if (ft_is_oddnbr(quotes[0]) || ft_is_oddnbr(quotes[1]))
		return (TRUE);
	return (FALSE);
}

char	*handle_open_quotes(t_shell *data, char *old, int *quotes)
{
	char	*new;
	char	c;

	c = '\0';
	c = identify_open_quote(old, c, quotes);
	data->quotes = TRUE;
	new = read_until_quote(c, old, 0, 0);
	return (new);
}
