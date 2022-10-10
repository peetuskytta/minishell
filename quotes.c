/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 07:53:34 by pskytta          ###   ########.fr       */
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

static void	read_until_quote(char c, char *new, int bytes_read)
{
	char	*extra;
	int		num_quotes;

	num_quotes = 0;
	extra = (char *)ft_memalloc(BUFFER);
	while (TRUE)
	{
		write_open_quote(c);
		bytes_read = read(0, extra, BUFFER);
		if (bytes_read > 0)
		{
			ft_strcat(new, extra);
			num_quotes = ft_chrstr(new, c);
			if (ft_is_oddnbr(num_quotes) == FALSE)
			{
				ft_memdel((void *)&(extra));
				break ;
			}
			ft_memset(extra, '\0', BUFFER);
		}
		else
		{
			ft_memdel((void *)&(extra));
			break ;
		}
	}
}

static char	identify_open_quote(char c, int *quote)
{
	if (ft_is_oddnbr(quote[0]))
		c = S_QUOTE;
	else if (ft_is_oddnbr(quote[1]))
		c = D_QUOTE;
	return (c);
}

static void	check_quote_amount(char *new, char *old)
{
	int		quotes[2];
	char	c;

	c = '\0';
	quotes[0] = ft_chrstr(old, S_QUOTE);
	quotes[1] = ft_chrstr(old, D_QUOTE);
	if (ft_is_oddnbr(quotes[0]) || ft_is_oddnbr(quotes[1]))
	{
		c = identify_open_quote(c, quotes);
		ft_strcpy(new, old);
		read_until_quote(c, new, 0);
		if (ft_strchr(new, BACKSLASH))
			new = NULL;
	}
	else
		ft_strcpy(new, old);
	//new[ft_strlen(new)] = '\0';
}

char	*handle_quotes(t_shell *data, char *old)
{
	char	buf[4096];

	ft_memset(buf, '\0', 4096);
	check_quote_amount(buf, old);
	data->quotes = TRUE;

	//buf[ft_strlen(buf)] = '\0';
	return (ft_strtrim(buf));
}

