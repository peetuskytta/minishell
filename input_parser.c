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

void	parse_input(t_shell *data, char *input)
{
	if (simple_input_check(input) == TRUE)
	{
		if (tokenize_input(data, input, 0) == TRUE)
		{
			if (check_if_builtin(data) == TRUE)
				reset_last_cmd_env(data, data->last_cmd);
			else
			{
				create_child_process(data);
				// set data->last_cmd to be the path+binary executed succesfully
				reset_last_cmd_env(data, data->last_cmd);
			}
		}
	}
	else
	{
		ft_putendl("Quoting detected: please handle it\nhandling, thanks for the info...");
		//if (tokenize_input(data, input, 0) == TRUE)
			//handle_command(data);
		//exit(1);
	}
	free_double_ptr(data->token);
}
