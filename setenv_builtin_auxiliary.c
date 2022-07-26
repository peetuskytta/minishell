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
	if (data->token_count != 2)
		return (FALSE);
	else if (data->token[1] == NULL || ft_strlen(data->token[1]) == 0)
		ft_putendl(NAME_ERROR);
	else if (ft_strchr(data->token[1], '='))
		ft_putendl(STR_ILLEGAL_CHAR);
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

void	env_variable_counter(t_shell *info, char **environ)
{
	while (environ[info->env_count] != NULL)
		info->env_count++;
}
