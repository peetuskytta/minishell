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

void	reset_env_value(t_shell *data, int i)
{
	int	len;

	if (data->token_count == 2)
	{
		len = ft_strlen(data->token[1]) + ft_strlen(data->token[2] + 1);
		ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
		ft_putendl("2");
		ft_memdel((void *)&data->environ[i]);
		data->environ[i] = ft_strnew(len);
		if (data->environ[i] == NULL)
			exit(EXIT_FAILURE);
		ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
		ft_putendl("3");
		ft_strcat(data->environ[i], data->token[1]);
		ft_strcat(data->environ[i], EQUALSIGN);
		ft_strcat(data->environ[i], data->token[2]);
	}
}

static char **plus_one_line(char **old_env, int rows)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (rows + 1));
	if (new_env == NULL)
		exit(EXIT_FAILURE);
	while (rows > i)
	{
		new_env[i] = ft_strdup(old_env[i]);
		ft_memdel((void *)&old_env[i]);
		i++;
	}
	free(old_env);
	return(new_env);
}

static void	add_env_variable(t_shell *data, int size)
{
	char	**new_env;
	int		len;

	new_env = plus_one_line(data->environ, size);
	size++;
	len = ft_strlen(data->token[1]) + ft_strlen(data->token[2]) + 1;
	new_env[--size] = ft_strnew(len);
	if (new_env[size] == NULL)
		exit(EXIT_FAILURE);
	ft_memset(new_env[size], '\0', len + 1);
	ft_strcat(new_env[size], data->token[1]);
	ft_strcat(new_env[size], EQUALSIGN);
	ft_strcat(new_env[size], data->token[2]);
	data->environ = new_env;
	data->env_count++;
}

static int	set_env_variable(t_shell *data)
{
	int	var_index;

	if (data->token_count == 2)
	{
		var_index = search_var_name(data->token[1], data);
		if (var_index > 0)
			reset_env_value(data, var_index);
		else
			add_env_variable(data, data->env_count);
		return (TRUE);
	}
	else
	{
		ft_putendl(SETENV_USAGE);
		return (FALSE);
	}
}

int	change_environ(t_shell *data, int id)
{
	if (setenv_name_error_check(data) == FALSE)
	{
		if (id == 1)
		{
			if (set_env_variable(data) == TRUE)
			{
				data->under = search_var_name("_", data);
				reset_env_value(data, data->under);
			}
			else
			{
				data->under = search_var_name("_", data);
				reset_env_value(data, data->under);
			}
		}
		if (id == 2)
			ft_putendl("unsetenv please...");
	}
	return (TRUE);
}
