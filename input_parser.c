/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:52:45 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/16 22:52:45 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	simple_input_check(char *input)
{
	if (ft_strchr(input, BACKSLASH))
		return (FALSE);
	else if (ft_strchr(input, SINGLEQUOTE))
		return (FALSE);
	else if (ft_strchr(input, DOUBLEQUOTE))
		return (FALSE);
	else
		return (TRUE);
}

static int	tokenize_input(t_shell *data, char *input, int i)
{
	while (input[i] != '\0')
	{
		if (ft_is_wspace(input[i]))
			input[i] = ' ';
		i++;
	}
	data->token = ft_strsplit(input, ' ');
	if (data->token == NULL)
		ft_putendl(MALLOC_FAIL);
	i = 0;
	while (data->token[i] != NULL)
	{
		data->token_count++;
		i++;
	}
	if (data->token == NULL)
		data->token_count = -1;
	return (TRUE);
}

void	parse_input(t_shell *data, char *input)
{
	if (simple_input_check(input) == TRUE)
	{
		if (tokenize_input(data, input, 0) == TRUE)
			execute_command(data);
	}
	else
		ft_putendl("Quoting detected: handle it please");
	free_double_ptr(data->token);
}
