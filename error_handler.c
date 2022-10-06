/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:46:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/06 15:46:13 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_print(char *sh, char *name, char *msg)
{
	ft_putstr_fd(sh, STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
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
		ft_putstr_fd(name, STDERR_FILENO);
		error_print(ARG_USAGE_1, name, ARG_USAGE_2);
	}
	return (FALSE);
}

int exec_error_check(t_shell *data, int check)
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
