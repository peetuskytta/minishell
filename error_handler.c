/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:46:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/26 17:31:30 by pskytta          ###   ########.fr       */
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
