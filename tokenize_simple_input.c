/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_simple_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:19:30 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/28 15:19:30 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_simple_input(t_shell *data, char *input, int i)
{
	while (input[i] != '\0')
	{
		if (ft_is_wspace(input[i]))
			input[i] = ' ';
		i++;
	}
	if (ft_word_count(input, ' ') == 0)
	{
		data->token = (char **)ft_memalloc(sizeof(char *) * (1 + 1));
		data->token[0] = ft_strdup(input);
		if (ft_strequ(data->token[0], SETENV) == 1)
			data->token[1] = ft_strdup("");
		else
			data->token[1] = NULL;
	}
	else
		data->token = ft_strsplit(input, ' ');
	i = 0;
	while (data->token[i++] != NULL)
		data->token_count++;
}

