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

/*
**	ft_strnew() exits if malloc fails.
*/
/*void	reset_env_value(t_shell *data, int i)
{
	int	len;

	len = ft_strlen(data->token[1]) + ft_strlen(data->token[2]);
	ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
	ft_memdel((void *)&data->environ[i]);
	data->environ[i] = ft_strnew(len);
	ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
	ft_strcat(data->environ[i], data->token[1]);
	ft_strcat(data->environ[i], EQUALSIGN);
	ft_strcat(data->environ[i], data->token[2]);
}*/

void	modify_env(t_shell *data, char *name, char *value, int i)
{
	//char	*value;
	//int		namelen;
	//int		len;

	//namelen = ft_strlen(name) + 1;
	//len = ft_strlen(data->environ[i]) - namelen;
	//value = ft_strsub(data->environ[i], namelen, len);
	i = search_var_name(name, data);
	ft_memset(data->environ[i], 0, ft_strlen(data->environ[i]));
	ft_memdel((void *)&data->environ[i]);
	data->environ[i] = join_n_and_v(name, value);
	//free(value);
}

/*
**	ft_strdup() exits if malloc fails.
*/
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
		ft_memdel((void *)&old_env[i++]);
	}
	free(old_env);
	new_env[rows++] = NULL;
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
			modify_env(data, data->token[1], data->token[2], 0);
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
	int	i;

	i = 0;
	if (setenv_name_error_check(data) == FALSE)
	{
		if (id == 1)
		{
			if (set_env_variable(data) == TRUE)
				reset_last_cmd_env(data);
		}
		else if (id == 2)
		{
			if (unset_env_variable(data) == TRUE)
				reset_last_cmd_env(data);
		}
		else if (id == 3)
		{
			while (data->env_count > i)
			{
				if (data->environ[i][0] != '\0')
					ft_putendl(data->environ[i]);
				i++;
			}
		}
		reset_last_cmd_env(data);
	}
	return (TRUE);
}
