/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/04 16:24:02 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static char	*copy_dq(char *string)
{
	char	temp[4096];
	int		start;
	int		ii;
	int		i;

	i = 0;
	ii = 0;
	ft_memset(temp, '\0', 4096);
	start = ft_strchr(string, D_QUOTE) - string;
	string += start;
	while (string[++i] != D_QUOTE)
		temp[ii++] = string[i];
	i++;
	if (string[i] != '\0')
	{
		while (!ft_is_ws_withoutnl(string[i]) && string[i + 1] != '\0')
			temp[ii++] = string[i++];
	}
	temp[ii] = '\0';
	return (ft_strcpy(temp, temp));
}

static char	*copy_sq(char *string)
{
	char	temp[4096];
	int		start;
	int		ii;
	int		i;

	i = 0;
	ii = 0;
	ft_memset(temp, '\0', 4096);
	start = ft_strchr(string, S_QUOTE) - string;
	string += start;
	while (string[++i] != S_QUOTE)
		temp[ii++] = string[i];
	temp[ii] = '\0';
	return (ft_strcpy(temp, temp));
}

static void	work_dq(char *temp, char *input, int *index)
{
	ft_putnbr_endl(index[0]);
	ft_strcat(temp, copy_dq(input + index[0]));
	index[0] = ft_strchr(input, D_QUOTE) - input + 1;
	index[0] += ft_strlen(temp) + 1;
	//ft_putendl(&input[index[0]]);
	index[1] = ft_strlen(temp);
}

static void	work_sq(char *temp, char *input, int *index)
{
	ft_strcat(temp, copy_sq(input));
	index[0] = ft_strchr(input, S_QUOTE) - input;
	index[0] += ft_strlen(temp) + 1;
	index[1] = ft_strlen(temp);
}

static char	*work_ws(char *temp, char *string, int *index, int *i)
{
	char	*token;
	char	*cpy;
	int		pos;

	pos = index[0];
	cpy = string;
	token = ft_strdup(temp);
	ft_memset(temp, '\0', 4096);
	while (ft_is_wspace(cpy[pos]))
	{
		index[0]++;
		pos++;
	}
	index[1] = 0;
	*i += 1;
	return (token);
}*/

/* index[0] = temp[pos] and index[1] = input[pos]*/
void	tokenize_complex_input(t_shell *data, char *input, int i)
{
	int		index[3];

	ft_memset(index, 0, sizeof(index));
	index[2] = (int)ft_word_count(input, ' ') + 1;
	data->token = (char **)ft_memalloc(sizeof(char *) * index[2] + 1);

	while (input[index[0]] != '\0')
	{
		if (ft_is_ws_withoutnl(input[index[0]]))
		{
			data->token[i++] = ft_strsub(input, index[1] + index[0], index[0]);
			while (ft_is_ws_withoutnl(input[index[0]]))
				index[0]++;
		}
		if (ft_is_ws_withoutnl(input[index[0]]))
		index[0]++;



	}
	ft_putendl(data->token[0]);
//	ft_putendl(data->token[1]);
	exit(1);
}

/*	while(TRUE)
	{
		while (input[index[0]] != '\0')
		{
			if (input[index[0]] == D_QUOTE)
			{
				work_dq(temp, input, index);
				ft_putstr("dq: ");
				ft_putendl(temp);
				data->token[i] = ft_strdup(temp);
				ft_memset(temp, '\0', 4096);
				index[1] = 0;
				break ;
			}
			else if (input[index[0]] == S_QUOTE)
			{
				work_sq(temp, input, index);
				//ft_putstr("sq: ");
				//ft_putendl(temp);
			}
			else if (input[index[0]] != '\0')
			{
				//if (input[index[0]] == WHITESPACE || input[index[0]] == TAB)
				//	index[0]++;
				//ft_putendl(temp);
				//exit(1);
				if (ft_is_ws_withoutnl(input[index[0]]))
				{
					index[0]++;
					//data->token[i] = ft_strdup(temp);
				}
				else
					temp[index[1]++] = input[index[0]++];
				if (input[index[0]] == '\0' || ft_is_ws_withoutnl(input[index[0]]))
				{
					data->token[i] = ft_strdup(temp);
					ft_memset(temp, '\0', 4096);
					//index[0] += index[1];
					index[1] = 0;
					break ;
				}
			}
		}
		i++;
		if (input[index[0]] == '\0')
			break ;
	}
	//ft_putnbr_endl(i);
	data->token[i] = NULL;
	i = 0;
	ft_putchar(NEWLINE);
	while (data->token[i] != NULL)
	{
		ft_putnbr(i);
		ft_putchar(WHITESPACE);
		ft_putendl(data->token[i]);
		data->token_count++;
		i++;
	}
	//exit(1);
}
*/




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
