/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 11:47:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/20 11:47:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_var_name(char *name, char **name_array, t_shell *data)
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

static void	reset_env_value(t_shell *data, int index)
{
	char	temp[4096];

	ft_memset(temp, '\0', ft_strlen(temp));
	ft_strcat(temp, data->environ_n[index]);
	ft_strcat(temp, "=");
	ft_memset(data->environ_v[index], 0, ft_strlen(data->environ_v[index]));
	ft_memdel((void *)&data->environ_v[index]);
	ft_memset(data->environ[index], 0, ft_strlen(data->environ[index]));
	data->environ_v[index] = ft_strdup(data->token[2]);
	data->environ[index] = ft_strjoin(temp, data->token[2]);
}

static void	set_env_variable(t_shell *data)
{
	int	var_index;

	var_index = search_var_name(data->token[1], data->environ_n, data);
	ft_putnbr_endl(var_index);
	if (var_index > 0)
		reset_env_value(data, var_index);
	else
		ft_putendl("add new environ");
}

int	change_environ(t_shell *data, int id)
{
	if (setenv_name_error_check(data) == FALSE)
	{
		if (id == 1)
		{
			set_env_variable(data);
		}
		if (id == 2)
		{
			ft_putendl("unsetenv please...");
		}
	}
	return (TRUE);
}
