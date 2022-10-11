/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:02:52 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/11 11:36:22 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Builtin function to print the tokens after "echo" command
**	checks for "-n" flag in order to print newline or not.
**	!!expand tokens differently in echo!!
*/
int	echo_driver(t_shell *data, int i)
{
	while (data->token[i] != NULL)
	{
		ft_putstr(data->token[++i]);
		ft_putchar(WHITESPACE);
	}
	if (data->no_nl == FALSE)
		ft_putchar(NEWLINE);
	return (TRUE);
}
