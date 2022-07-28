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

int	search_var_name(char *name, t_shell *data)
{
	int	i;

	i = 0;
	while (data->env_count > i)
	{
		if (ft_strnstr(data->environ[i], name, ft_strlen(name)) != NULL)
			return (i);
		i++;
	}
	return (0);
}

char	*join_n_and_v(char *name, char *value)
{
	char	temp[1024];

	ft_memset(temp, '\0', ft_strlen(temp));
	ft_strcat(temp, name);
	ft_strcat(temp, EQUALSIGN);
	name = temp;
	return (ft_strjoin(name, value));
}
