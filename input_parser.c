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

int	simple_input_check(char *input)
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
	if (data->quotes == TRUE)
		tokenize_complex_input(data, input, 0);
	else
		tokenize_simple_input(data, input, 0);
	if (check_if_builtin(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else if (initial_exec_checks(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else
		reset_last_cmd_env(data, 0);
}
// set data->cmd to be the path+binary executed succesfully
