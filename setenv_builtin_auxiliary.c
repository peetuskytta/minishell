/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin_auxiliary.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:53:27 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/21 15:53:27 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setenv_name_error_check(t_shell *data)
{
	if (data->token[1] == NULL)
	{
		ft_putendl(NULL_STR);
		return (TRUE);
	}
	else if (ft_strlen(data->token[1]) == 0)
	{
		ft_putendl(ZERO_LEN_STR);
		return (TRUE);
	}
	else if (ft_strchr(data->token[1], 61))
	{
		ft_putendl(STR_ILLEGAL_CHAR);
		return (TRUE);
	}
	return (FALSE);
}
