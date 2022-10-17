/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:46:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/14 14:48:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_print(char *sh, char *name, char *msg)
{
	ft_putstr_fd(sh, 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(msg, 2);
}

int	exec_error_message(int id, char *name)
{
	if (id == 1)
		error_print(MINISH, name, EXEC_NO_ACCESS);
	if (id == 2)
		error_print(MINISH, name, CMD_NOT_FOUND);
	if (id == 3)
		error_print(MINISH, name, IS_A_DIR);
	if (id == 5)
		error_print(MINISH, name, NO_FILE_OR_DIR);
	if (id == 4)
	{
		error_print(MINISH, name, ARG_REQUIRED);
		ft_putstr_fd(name, 2);
		error_print(ARG_USAGE_1, name, ARG_USAGE_2);
	}
	return (FALSE);
}

int	exec_error_check(t_shell *data, int check)
{
	if (check == FALSE)
		return (exec_error_message(2, data->token[0]));
	else if (check == 2)
		return (exec_error_message(1, data->token[0]));
	else if (check == 3)
		return (exec_error_message(3, data->token[0]));
	else if (check == 4)
		return (exec_error_message(4, data->token[0]));
	else if (check == 5)
		return (exec_error_message(5, data->token[0]));
	else
		return (TRUE);
}

int	cd_error_message(char *name, int id)
{
	if (id == 1)
	{
		if (!name)
			error_print(CD_SH, name, NO_FILE_OR_DIR);
		else
			error_print(CD_SH, name, NO_FILE_OR_DIR);
	}
	else if (id == 2)
		error_print(CD_SH, name, NO_FILE_OR_DIR);
	else if (id == 3)
		return (3);
	else if (id == 4)
		error_print(CD_SH, name, CD_NO_ACCESS);
	return (3);
}

int	setenv_error_check(t_shell *data)
{
	if (ft_strequ(data->token[0], SETENV) == TRUE)
	{
		if (data->token_count <= 1)
			ft_putendl_fd(SETENV_USAGE, STDERR_FILENO);
		if (data->token_count == 2)
		{
			if (ft_strchr(data->token[1], '=')
				|| ft_isdigit(data->token[1][0])
				|| !ft_isalpha(data->token[1][0]))
			{
				ft_putstr(MINISH);
				error_print("setenv: ", data->token[1], NOT_IDENTIFIER);
				return (FALSE);
			}
			else
				return (TRUE);
		}
		else if (data->token_count > 2)
			ft_putendl_fd(SET_TOO_MANY_ARG, 2);
		return (FALSE);
	}
	else
		return (FALSE);
}
