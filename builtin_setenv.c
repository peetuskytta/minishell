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
**	This function modifies/changes the existing environment variable's VALUE.
**	First the index search is done
*/
void	modify_env(t_shell *data, char *name, char *value, int i)
{
	i = search_var_name(name, data);
	if (i < 0)
		add_env_variable(data, name, value);
	i = search_var_name(name, data);
	ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
	ft_memdel((void *)&data->environ[i]);
	data->environ[i] = join_n_and_v(name, value);
}

/*
**	Adds one line to the environment in order to add the new variable
**	to the environment.
**	NOTE: ft_strdup() and ft_memalloc() exit if malloc() fails.
*/
static char	**plus_one_line(t_shell *data, char **old_env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)ft_memalloc(sizeof(char *) * (data->env_count + 2));
	while (old_env[i] != NULL)
	{
		new_env[i] = ft_strdup(old_env[i]);
		ft_memdel((void *)&(old_env[i]));
		i++;
	}
	new_env[i] = NULL;
	free_array(old_env);
	return (new_env);
}

/*
**	Adds new environment variable to the environment. Plus_one_line function
**	returns new array of arrays to fit the existing and the new variable.
*/
void	add_env_variable(t_shell *data, char *name, char *val)
{
	int		len;
	char	*new_var;

	data->environ = plus_one_line(data, data->environ);
	len = ft_strlen(name) + ft_strlen(val) + 1;
	new_var = ft_strnew(len);
	ft_memset(new_var, '\0', len + 1);
	ft_strcat(new_var, name);
	ft_strcat(new_var, EQUAL_SIGN);
	ft_strcat(new_var, val);
	data->environ[data->env_count] = ft_strdup(new_var);
	data->env_count++;
	ft_memdel((void *)&(new_var));
}

/*
**	Checks if environment variable is modified or a new one is added.
**	In case 'var_index' is larger or equal to 0 the variable exists and
**	its value is modified in the environment. Otherwise the name=value
**	is added to the environment.
*/
static int	set_env_variable(t_shell *data)
{
	int	var_index;

	if (data->token_count == 2)
	{
		var_index = search_var_name(data->token[1], data);
		if (var_index >= 0)
			modify_env(data, data->token[1], data->token[2], 0);
		else
			add_env_variable(data, data->token[1], data->token[2]);
		return (TRUE);
	}
	else
		return (FALSE);
}

/*
**	This function directs the actions for 'setenv' and 'unsetenv' builtins.
**	If id==1 it is 'setenv', if id==2 it is 'unsetenv'.
*/
int	change_environ(t_shell *data, int id)
{
	check_expansion(data, 0);
	if (setenv_error_check(data) == TRUE && id == 1)
	{
		if (set_env_variable(data) == TRUE)
			reset_last_cmd_env(data, 0);
	}
	else if (unset_error_check(data) == TRUE && id == 2)
	{
		if (unset_env_variable(data) == TRUE)
			reset_last_cmd_env(data, 0);
	}
	reset_last_cmd_env(data, 0);
	return (TRUE);
}
