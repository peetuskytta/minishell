/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/06 00:31:39 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static int	check_if_quote(char c)
{
	return (c == S_QUOTE || c == D_QUOTE);
}

static char	*find_token(char *input, int *totes, int i, int closed)
{
	char	*token;
	int		d_quote;
	int		s_quote;
	int		pos;

	s_quote = 0;
	d_quote = 0;
	pos = 0;
	//ft_putnbr_endl(ft_strlen(input));
	token = ft_strnew(ft_strlen(input));
	//exit(1);
	while (ft_is_ws_withoutnl(input[i]) && (*totes)++)
		i++;
	while (input[i])
	{
		if (check_if_quote(input[i]) == TRUE)
		{
			while (input[i] == D_QUOTE && s_quote == FALSE)
			{
				i++;
				d_quote += 1;
				*totes += 1;
			}
			while (input[i] == S_QUOTE && d_quote == FALSE)
			{
				i++;
				s_quote += 1;
				*totes += 1;
			}
			if (d_quote >= 2 || s_quote >= 2)
				closed = TRUE;
		}
		if ((ft_is_ws_withoutnl(input[i]) && closed) || (ft_is_ws_withoutnl(input[i]) && s_quote + d_quote == FALSE))
		{
			*totes += 1;
			//printf("token-->{%s}\n", token);
			break ;
		}
		if ((input[i] && closed == FALSE) || (!ft_is_ws_withoutnl(input[i] && closed == TRUE)))
		{
			token[pos++] = input[i++];
			*totes += 1;
		}
	}
	if (input[ft_strlen(token) + 1] == '\0')
		return (NULL);
	//ft_putendl(token);
	//ft_putnbr_endl(*totes);
	return (token);
}


void	tokenize_complex_input(t_shell *data, char *input, int index)
{
	int	alloc_count;
	int	i;

	i = 0;
	alloc_count = (int)ft_word_count(input, ' ') + 1;
	data->token = (char **)ft_memalloc(sizeof(char *) * alloc_count + 1);
	alloc_count = 0;
	while (input[i])
	{
		data->token[alloc_count] = find_token(input, &index, i, 0);
		printf("token[%d]-->{%s}\n", alloc_count, data->token[alloc_count]);
		//exit(1);
		if (data->token[alloc_count] == NULL)
			break ;
		i = index;
		ft_putnbr_endl(i);
		alloc_count++;
	}
	exit(1);
}





/*
static int	find_open_quote(char *str, int pos)
{
	char	chr;

	if (ft_strchr(str + pos, D_QUOTE))
		chr = D_QUOTE;
	else
		chr = S_QUOTE;
	ft_putchar(chr);
	ft_putchar(NEWLINE);
	return (chr);
}

void	tokenize_complex_input(t_shell *data, char *buf, int i, int quote)
{
	char	*tmp;
	char	chr;
	int		k;
	int		p;

	k = 0;
	p = 0;
	//ft_putendl(buf);
	tmp = ft_strtrim(buf);
	//ft_putendl(tmp);
	chr = find_open_quote(buf, p);
	data->token = (char **)ft_memalloc(sizeof(char *) * ((int)ft_word_count(buf, ' ') + 1));
	while (tmp[k] != '\0')
	{
		while (quote != 2)
		{
			if (chr == '\'' || chr == '\"')
			{
				if (tmp[k++] == chr)
					quote++;
			}
			else
				k++;
		}
		if (quote == 2)
		{
			while (!ft_is_ws_withoutnl(tmp[k]))
			{
				if (tmp[k] == '\0')
					break;
				k++;
			}
			data->token[i] = ft_strsub(tmp, p, k);
			i++;
			p += ++k;
			quote = 0;
			chr = find_open_quote(tmp, p);
		}
	}
//	ft_putchar(NEWLINE);
	data->token[i] = NULL;
	i = 0;
	while (data->token[i] != NULL)
	{
		ft_putendl(data->token[i++]);
		data->token_count++;
	}
	//exit(1);
	ft_memdel((void *)&(tmp));
}
*/
