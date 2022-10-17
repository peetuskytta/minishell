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

/*
** Checks if the command given is "exit" and if TRUE returns FALSE.
**	exit happens in main.c
*/
static int	exit_or_not(char *token, char *buf)
{
	if (ft_strequ(token, "exit") == TRUE)
	{
		create_or_append_history(token);
		ft_memdel((void *)&(buf));
		ft_putendl_fd(EXIT, STDOUT_FILENO);
		return (FALSE);
	}
	else
		return (TRUE);
}

/*
**	Checks for input's simplicity. If quotes are found it returns FALSE.
*/
int	simple_input_check(char *input)
{
	if (ft_strchr(input, S_QUOTE))
		return (FALSE);
	if (ft_strchr(input, D_QUOTE))
		return (FALSE);
	else
		return (TRUE);
}

/*
**	Parse input function tokenizes the input and continues to drive
**	action further to bultin checks, executable checks or resetting
**	the last command value.
*/
int	parse_input(t_shell *data, char *input)
{
	if (data->quotes == TRUE)
	{
		tokenize_complex_input(data, input, 0);
		check_expansion(data, 0);
	}
	else
	{
		tokenize_simple_input(data, input, 0);
		check_expansion(data, 0);
	}
	if (exit_or_not(data->token[0], input) == FALSE)
		return (FALSE);
	if (check_if_builtin(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else if (initial_exec_checks(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else
		reset_last_cmd_env(data, 0);
	ft_memdel((void *)&(data->pwd));
	if (data->quotes == TRUE)
		data->quotes = FALSE;
	return (TRUE);
}
