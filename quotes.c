/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:15 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 12:45:19 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static void	write_open_quote(char c)
{
	if (c == S_QUOTE)
		ft_putstr_fd(S_QUOTE_ARROW, 1);
	if (c == D_QUOTE)
		ft_putstr_fd(D_QUOTE_ARROW, 1);
}

static char	*read_until_quote(char c, char *old, int bytes_read)
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
			//printf("len-> %zu\told-> %s\n", ft_strlen(old), old);
			//pr/intf("len-> %zu\told-> %s\n", ft_strlen(extra), extra);
			ft_strcat(old, extra);
			num_quotes = ft_chrstr(old, c);
			if (ft_is_oddnbr(num_quotes) == FALSE)
				break ;
			ft_memset(extra, '\0', BUFFER);
		}
		else
			break ;
	}
	ft_memdel((void *)&(extra));
	return (old);
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

char	*handle_open_quotes(t_shell *data, char *old, int *quotes)
{
	char	*new;
	char	c;

	c = '\0';
	c = identify_open_quote(old, c, quotes);
	data->quotes = TRUE;
	//if (c == S_QUOTE || c == D_QUOTE)
	new = read_until_quote(c, old, 0);
	//else
	//	return (ft_strdup(old));
	return (ft_strdup(new));
}

