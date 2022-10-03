/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/03 17:29:40 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_open_quote(char *str, int pos)
{
	char	chr;

	if (ft_strchr(str + pos, D_QUOTE))
		chr = D_QUOTE;
	else
		chr = S_QUOTE;
	return (chr);
}

void	tokenize_complex_input(t_shell *data, char *buf, int i, int quote)
{
	char	chr;
	int		k;
	int		p;

	k = 0;
	p = 0;
	ft_putendl(buf);
	chr = find_open_quote(buf, p);
	data->token = (char **)ft_memalloc(sizeof(char *) * ((int)ft_word_count(buf, ' ') + 1));
	while (buf[k] != '\0')
	{
		while (quote != 2)
		{
			if (buf[k++] == chr)
				quote++;
		}
		if (quote == 2)
		{
			while (!ft_is_wspace(buf[k]))
			{
				if (buf[k] == '\0')
					break;
				k++;
			}
			data->token[i] = ft_strsub(buf, p, k);
			i++;
			p += ++k;
			quote = 0;
			chr = find_open_quote(buf, p);
		}
	}
	ft_putchar(NEWLINE);
	data->token[i] = NULL;
	i = 0;
	while (data->token[i] != NULL)
		ft_putendl(data->token[i++]);
	//exit(1);
}
