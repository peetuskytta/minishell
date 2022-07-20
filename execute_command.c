/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:15:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/20 11:15:57 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_builtin(t_shell *data)
{
	if (ft_strequ(data->token[0], CD))
		ft_putendl("function pointer to CD");
	else if (ft_strequ(data->token[0], ECHO))
		ft_putendl("function pointer to ECHO");
	else if (ft_strequ(data->token[0], SETENV))
		ft_putendl("function pointer to SETENV");
	else if (ft_strequ(data->token[0], UNSETENV))
		ft_putendl("function pointer to UNSETENV");
	return (false);
}

void	execute_command(t_shell *data)
{
	if (check_if_builtin(data) == false)
		ft_putendl("fork and execve");
}
