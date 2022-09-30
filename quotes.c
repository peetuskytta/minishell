/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/30 16:55:37 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_open_quote(char c)
{
	if (c == SINGLEQUOTE)
		ft_putstr_fd(S_QUOTE, 1);
	if (c == DOUBLEQUOTE)
		ft_putstr_fd(D_QUOTE, 1);
}

static void	read_until_quote(char c, char *new)
{
	char	*extra;
	int		bytes_read;
	int		num_quotes;

	bytes_read = 0;
	num_quotes = 0;
	extra = (char *)ft_memalloc(BUFFER);
	ft_memset(extra, '\0', BUFFER);
	while (TRUE)
	{
		write_open_quote(c);
		bytes_read = read(0, extra, BUFFER);
		if (bytes_read < 0)
			break ;
		ft_strcat(new, extra);
		num_quotes = ft_chrstr(new, c);
		if (ft_is_oddnbr(num_quotes) == FALSE)
		{
			ft_memdel((void *)&(extra));
			break ;
		}
		ft_memset(extra, '\0', BUFFER);
	}
}

static char	identify_open_quote(char c, int *quote)
{
	if (ft_is_oddnbr(quote[0]))
		c = SINGLEQUOTE;
	else if (ft_is_oddnbr(quote[1]))
		c = DOUBLEQUOTE;
	return (c);
}

static void	check_quote_amount(char *new, char *old)
{
	int		quotes[2];
	char	c;

	c = '\0';
	quotes[0] = ft_chrstr(old, SINGLEQUOTE);
	quotes[1] = ft_chrstr(old, DOUBLEQUOTE);
	if (ft_is_oddnbr(quotes[0]) || ft_is_oddnbr(quotes[1]))
	{
		c = identify_open_quote(c, quotes);
		ft_strcpy(new, old);
		read_until_quote(c, new);
	}
	else
		ft_strcpy(new, old);
	new[ft_strlen(new) - 1] = '\0';
}

char	*handle_quotes(t_shell *data, char *old)
{
	char	*buf;

	buf = ft_strnew(ft_strlen(old) + 2048);
	ft_memset(buf, '\0', sizeof(buf));
	check_quote_amount(buf, old);
	if (ft_strchr(buf, BACKSLASH))
	{
		ft_putendl_fd("minishell: '\\\' as input not supported.", 2);
		return ((char *)ft_memset(buf, '\0', ft_strlen(buf)));
	}
	clean_input_string(data, buf, 0);
	return (buf);
}
