/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:33:30 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/01 11:33:30 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_for_spaces(t_shell *data, char *input, int i)
{
	char	temp[4096];
	int		tok;
	int		inp_i;

	tok = 1;
	inp_i = 0;
	ft_memset(temp, '\0', 4096);
	while (input[i] != '\0')
	{
		if (input[i] == BACKSLASH)
			temp[inp_i] = input[++i];
		if (input[i + 1] == ' ')
		{
			temp[++inp_i] = '\0';
			data->token[tok] = ft_strdup(temp);
			ft_memset(temp, '\0', 4096);
			tok++;
		}
		temp[inp_i++] = input[i++];
	}
	temp[inp_i] = '\0';
	data->token[tok] = ft_strdup(temp);
}

int	tokenize_input(t_shell *data, char *input, int i)
{
	if (ft_strchr(input, BACKSLASH))
		check_for_spaces(data, input, 0);
	while (input[i] != '\0')
	{
		if (ft_is_wspace(input[i]))
			input[i] = ' ';
		i++;
	}
	if (ft_word_count(input, ' ') == 0)
	{
		data->token = (char **)malloc(sizeof(char *) * (1 + 1));
		if (!data->token)
			exit(EXIT_FAILURE);
		data->token[0] = ft_strdup(input);
		if (ft_strequ(data->token[0], SETENV) == 1)
			data->token[1] = ft_strdup("");
		else
			data->token[1] = NULL;
	}
	else
	{
		data->token = ft_strsplit(input, ' ');
	}
	i = 0;
	while (data->token[i++] != NULL)
		data->token_count++;
	return (TRUE);
}
