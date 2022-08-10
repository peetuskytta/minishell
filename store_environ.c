/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 23:35:20 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/15 23:35:20 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_variable_counter(t_shell *data, char **inherited_variables)
{
	while (inherited_variables[data->env_count] != NULL)
		data->env_count++;
}

static void	allocate_envp(t_shell *data, char **env)
{
	int	i;

	i = 0;
	env_variable_counter(data, env);
	data->environ = (char **)malloc(sizeof(char *) * (data->env_count + 1));
	if (data->environ == NULL)
		exit(EXIT_FAILURE);
	while (env[i] != NULL)
	{
		data->environ[i] = ft_strdup(env[i]);
		i++;
	}
	data->environ[data->env_count] = NULL;
}

static void	split_path_variable(t_shell *data, int i)
{
	char	*var;

	while (data->env_count > i)
	{
		if (ft_strnstr(data->environ[i], "PATH", 4) != NULL)
			break;
		i++;
	}
	var = ft_strsub(data->environ[i], 5, ft_strlen(data->environ[i]) - 5);
	data->split_path = ft_strsplit(var, ':');
	if (data->split_path == NULL)
		exit(EXIT_FAILURE);
	ft_memset(var, 0, ft_strlen(var));
	free(var);
}

void	store_environ_variables(t_shell *data, char **env)
{
	char	*pwd;
	int		i;

	allocate_envp(data, env);
	split_path_variable(data, 0);
	i = search_var_name("PWD", data);
	pwd = ft_strsub(data->environ[i], 4, ft_strlen(data->environ[i]) - 4);
	modify_env(data, "SHELL", pwd, 0);
	ft_memset(pwd, 0, ft_strlen(pwd));
	free(pwd);
}
