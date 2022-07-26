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
	char	temp[1024];

	ft_memset(temp, '\0', ft_strlen(temp));
	ft_strcat(temp, name);
	ft_strcat(temp, "=");
	name = temp;
	return (ft_strjoin(name, value));
}

static void	reset_env_value(t_shell *data, int i)
{
	ft_memset(data->environ[i], 0, ft_strlen(data->environ[i]));
	ft_memset(data->environ_v[i], 0, ft_strlen(data->environ_v[i]));
	ft_memdel((void *)&data->environ_v[i]);
	data->environ_v[i] = ft_strdup(data->token[2]);
	if (data->environ_v[i] == NULL)
		exit(EXIT_FAILURE);
	data->environ[i] = join_n_and_v(data->environ_n[i], data->token[2]);
	if (data->environ[i] == NULL)
		exit(EXIT_FAILURE);
}

static void	add_env_variable(t_shell *data, int size)
{
	char	temp[1024];
	int		len;

	len = ft_strlen(data->token[1] + 1) + ft_strlen(data->token[2]);
	ft_memset(temp, '\0', 1024);
	ft_strcat(temp, data->token[1]);
	ft_strcat(temp, EQUALSIGN);
	ft_strcat(temp, data->token[2]);
	data->environ[size] = ft_strncpy(data->environ[size], temp, len);
	ft_putendl(data->environ[size]);
	data->env_count++;
}

static void	set_env_variable(t_shell *data)
{
	int	var_index;

	var_index = search_var_name(data->token[1], data->environ_n, data);
	if (var_index > 0)
		reset_env_value(data, var_index);
	else
		add_env_variable(data, data->env_count + 1);
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
