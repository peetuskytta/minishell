/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec_auxiliary.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:21:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/01 13:44:44 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_error_message(int id, char *name)
{
	if (id == 1)
	{
		ft_putstr(MINISH);
		ft_putstr(name);
		ft_putendl(EXEC_NO_ACCESS);
	}
	if (id == 2)
	{
		ft_putstr(MINISH);
		ft_putstr(name);
		ft_putendl(CMD_NOT_FOUND);
	}
	if (id == 3)
	{
		ft_putstr(MINISH);
		ft_putstr(name);
		ft_putendl(IS_A_DIR);
	}
	return (FALSE);
}
