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
		return (false);
	else if (ft_strchr(input, SINGLEQUOTE))
		return (false);
	else if (ft_strchr(input, DOUBLEQUOTE))
		return (false);
	else
		return (true);
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
	return (true);
}

void	parse_input(t_shell *data, char *input)
{
	if (simple_input_check(input) == true)
	{
		if (tokenize_input(data, input, 0) == true)
			execute_command(data);
	}
	else
		ft_putendl("Quoting detected: handle it please");
	cleanup_and_free(data->token);
}
