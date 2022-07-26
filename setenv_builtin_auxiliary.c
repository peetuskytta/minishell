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
	else if (ft_strchr(data->token[1], '='))
	{
		ft_putendl(STR_ILLEGAL_CHAR);
		return (TRUE);
	}
	return (FALSE);
}

int	search_var_name(char *name, char **name_array, t_shell *data)
{
	int	i;

	i = 0;
	while (data->env_count > i)
	{
		if (ft_strequ(name, name_array[i]) == TRUE)
			return (i);
		i++;
	}
	return (0);
}

