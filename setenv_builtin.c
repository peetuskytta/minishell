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

static char *join_n_and_v(char *name, char *value)
{
	char	temp[1966];

	ft_memset(temp, '\0', ft_strlen(temp));
	ft_strcat(temp, name);
	ft_strcat(temp, "=");
	name = temp;
	return (ft_strjoin(name, value));
}

static void	reset_env_value(t_shell *data, int index)
{
	ft_memset(data->environ[index], 0, ft_strlen(data->environ[index]));
	ft_memset(data->environ_v[index], 0, ft_strlen(data->environ_v[index]));
	ft_memdel((void *)&data->environ_v[index]);
	data->environ_v[index] = ft_strdup(data->token[2]);
	if (data->environ_v[index] == NULL)
		exit(1);
	data->environ[index] = join_n_and_v(data->environ_n[index], data->token[2]);
	if (data->environ[index] == NULL)
		exit(1);
}

static void	set_env_variable(t_shell *data)
{
	int	var_index;

	var_index = search_var_name(data->token[1], data->environ_n, data);
	if (var_index > 0)
		reset_env_value(data, var_index);
	else
		ft_putendl("add new variable");
}

int	change_environ(t_shell *data, int id)
{
	if (setenv_name_error_check(data) == FALSE)
	{
		if (id == 1)
			set_env_variable(data);
		if (id == 2)
			ft_putendl("unsetenv please...");
	}
	return (TRUE);
}
