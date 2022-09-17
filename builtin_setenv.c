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
**	This function modifies the existing environment variable's VALUE.
*/
void	modify_env(t_shell *data, char *name, char *value, int i)
{
	i = search_var_name(name, data);
	if (i < 0 && ft_strequ("OLDPWD", name) == 1)
		add_env_variable(data, "OLDPWD", "", data->env_count);
	ft_memset(data->environ[i], 0, ft_strlen(data->environ[i]));
	ft_memdel((void *)&data->environ[i]);
	data->environ[i] = join_n_and_v(name, value);
}

/*
**	Adds one line to the environment in order to add the new variable
**	to the environment.
**	NOTE: ft_strdup() and ft_memalloc() exit if malloc() fails.
*/
static char	**plus_one_line(char **old_env, int rows)
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
	return (new_env);
}

void	add_env_variable(t_shell *data, char *name, char *val, int size)
{
	char	**new_env;
	int		len;

	new_env = plus_one_line(data->environ, size);
	size++;
	len = ft_strlen(name) + ft_strlen(val) + 1;
	new_env[--size] = ft_strnew(len);
	if (new_env[size] == NULL)
		exit(EXIT_FAILURE);
	ft_memset(new_env[size], '\0', len + 1);
	ft_strcat(new_env[size], name);
	ft_strcat(new_env[size], EQUALSIGN);
	ft_strcat(new_env[size], val);
	data->environ = new_env;
	data->env_count++;
}

static int	set_env_variable(t_shell *data)
{
	int	var_index;
	int	count;

	count = data->env_count;
	if (data->token_count == 2)
	{
		var_index = search_var_name(data->token[1], data);
		if (var_index > 0)
			modify_env(data, data->token[1], data->token[2], 0);
		else
			add_env_variable(data, data->token[1], data->token[2], count);
		return (TRUE);
	}
	if (data->token_count == 1)
		return (TRUE);
	else
		return (FALSE);
}

void	setenv_different_input(t_shell *data, int i)
{
	char	**copy;
	char	buf[1024];

	copy = NULL;
	ft_memset(buf, '\0', 1024);
	if (data->token[1][0] == '=' || ft_isdigit(data->token[1][0]))
		error_print(MINISH, data->token[1], NOT_IDENTIFIER);
	else
	{
		copy = ft_strsplit(data->token[1], '=');
		ft_free_arr_of_arrays(data->token);
		ft_strcat(buf, SETENV);
		ft_strcat(buf, " ");
		while (ft_is_wspace(copy[0][i]))
			i++;
		ft_strcat(buf, copy[0] + i);
		ft_strcat(buf, " ");
		ft_strcat(buf, copy[1]);
		ft_free_arr_of_arrays(copy);
		data->token = ft_strsplit(buf, ' ');
		ft_memset(buf, '\0', 1024);
		data->token_count++;
	}
}

int	change_environ(t_shell *data, int id)
{
	check_expansion(data, 0);
	if (setenv_error_check(data) == TRUE && id == 1)
	{
		if (set_env_variable(data) == TRUE)
			reset_last_cmd_env(data, data->last_cmd);
	}
	else if (unset_error_check(data) == TRUE && id == 2)
	{
		if (unset_env_variable(data) == TRUE)
			reset_last_cmd_env(data, data->last_cmd);
	}
	reset_last_cmd_env(data, data->last_cmd);
	return (TRUE);
}
