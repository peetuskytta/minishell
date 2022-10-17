/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:07:54 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/14 14:07:54 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_variable_counter(t_shell *data, char **inherited_variables)
{
	while (inherited_variables[data->env_count] != NULL)
		data->env_count++;
}

/*
**	Allocates memory for environment and copies them from the **envp (brought
**	from main).
*/
static void	allocate_envp(t_shell *data, char **env)
{
	int	i;
	int	count;

	i = 0;
	env_variable_counter(data, env);
	count = data->env_count;
	data->environ = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	while (env[i] != NULL)
	{
		data->environ[i] = ft_strdup(env[i]);
		i++;
	}
	data->environ[data->env_count] = NULL;
}

/*
**	Function that splits the PATH variable into individual tokens.
*/
void	split_path_variable(t_shell *data, int i, int len)
{
	char	*var;
	char	*temp;

	if (data->split_path != NULL)
		free_array(data->split_path);
	if (data->env_count == 0)
		return ;
	while (data->env_count > i)
	{
		len = (int)(ft_strchr(data->environ[i], '=') - data->environ[i]);
		temp = ft_strsub(data->environ[i], 0, len);
		if (ft_strequ(temp, "PATH") == TRUE)
			break ;
		ft_strdel(&temp);
		i++;
	}
	if (data->env_count == i)
		return ;
	ft_strdel(&temp);
	var = ft_strsub(data->environ[i], 5, ft_strlen(data->environ[i]) - 5);
	data->split_path = ft_strsplit(var, ':');
	ft_memdel((void *)&(var));
}

/*
**	Starts the process of allocating memory for the environment variables
**	This function also sets a value to some variables.
*/
void	store_environ_variables(t_shell *data, char **env)
{
	int		var_i;

	allocate_envp(data, env);
	var_i = search_var_name("OLDPWD", data);
	if (var_i > 0)
		modify_env(data, "OLDPWD", "", 0);
	var_i = search_var_name("_", data);
	if (var_i < 0)
		add_env_variable(data, "_", "");
	var_i = search_var_name("SHLVL", data);
	if (var_i < 0)
		add_env_variable(data, "SHLVL", "1");
	else
		++data->environ[var_i][6];
	split_path_variable(data, 0, 0);
}
