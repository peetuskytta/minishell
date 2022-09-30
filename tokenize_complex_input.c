/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:12:21 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/30 09:09:45 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static char	*copy_dq(char *string)
{
	char	temp[1024];
	int		start;
	int		ii;
	int		i;

	i = 0;
	ii = 0;
	ft_memset(temp, '\0', 1024);
	start = ft_strchr(string, DOUBLEQUOTE) - string;
	string += start;
	while (string[++i] != DOUBLEQUOTE)
		temp[ii++] = string[i];
	temp[ii] = '\0';
	return (ft_strcpy(temp, temp));
}

static char	*copy_sq(char *string)
{
	char	temp[1024];
	int		start;
	int		ii;
	int		i;

	i = 0;
	ii = 0;
	ft_memset(temp, '\0', 1024);
	start = ft_strchr(string, SINGLEQUOTE) - string;
	string += start;
	while (string[++i] != SINGLEQUOTE)
		temp[ii++] = string[i];
	temp[ii] = '\0';
	return (ft_strcpy(temp, temp));
}

static void	work_dq(char *temp, char *input, int *index)
{
	ft_strcat(temp, copy_dq(input));
	index[0] = ft_strchr(input, DOUBLEQUOTE) - input;
	index[0] += ft_strlen(temp) + 2;
	index[1] = ft_strlen(temp);
}

static void	work_sq(char *temp, char *input, int *index)
{
	ft_strcat(temp, copy_sq(input));
	//exit(1);
	index[0] = ft_strchr(input, SINGLEQUOTE) - input;
	index[0] += ft_strlen(temp) + 2;
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
	ft_memset(temp, '\0', 1024);
	while (ft_is_wspace(cpy[pos]))
	{
		index[0]++;
		pos++;
	}
	index[1] = 0;
	*i += 1;
	return (token);
}

// index[0] = temp[pos] and index[1] = input[pos]
void	tokenize_complex_input(t_shell *data, char *input, int i)
{
	char	temp[1024];
	int		index[2];

	ft_memset(index, 0, sizeof(index));
	ft_memset(temp, '\0', 1024);
	data->token = (char **)malloc(sizeof(char *) * (200));
	ft_memset(data->token, 0, sizeof(data->token));
	allocation_check(data->token);
	while (input[index[0]] != '\0')
	{
		if (input[index[0]] == DOUBLEQUOTE)
		{
			//ft_putchar(input[index[0]]);
			work_dq(temp, input, index);
			//exit(1);
			//ft_putstr("dq: ");
			//ft_putendl(temp);
		}
		if (input[index[0]] == SINGLEQUOTE)
		{
			work_sq(temp, input, index);
			//ft_putstr("sq: ");
			//ft_putendl(temp);
		}
		if (input[index[0]] == WHITESPACE)
		{
			data->token[i] = work_ws(temp, input, index, &i);
			ft_putstr("ws: ");
			ft_putendl(data->token[i - 1]);
			ft_putstr("char in input: ");
			ft_putchar(input[index[0]]);
			ft_putstr("\ninput index: ");
			ft_putnbr_endl(index[0]);
			ft_putstr("temp index: ");
			ft_putnbr_endl(index[1]);
		}
		else if (input[index[0]] != '\0')
		{
			temp[index[1]++] = input[index[0]++];
			ft_putstr("norm: ");
			ft_putendl(temp);
			ft_putstr("char in input: ");
			ft_putchar(input[index[0]]);
			ft_putchar(NEWLINE);
		}
	}
	data->token[i] = ft_strdup(temp);
	data->token[i + 1] = NULL;
	i = 0;
	while (data->token[i] != NULL)
	{
		ft_putnbr(i);
		ft_putchar(WHITESPACE);
		ft_putendl(data->token[i]);
		i++;
	}
	//exit(1);
}
*/