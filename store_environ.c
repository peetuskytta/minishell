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

static void	allocate_envp(t_shell *data, char **env)
{
	int	i;

	i = 0;
	env_variable_counter(data, env);
	data->environ = (char **)malloc(sizeof(char *) * data->env_count + 1);
	if (data->environ == NULL)
		exit(EXIT_FAILURE);
	while (env[i] != NULL)
	{
		data->environ[i] = ft_strdup(env[i]);
		if (data->environ[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
}

static void	save_env_value(t_shell *info, int start, int i)
{
	int	len;

	info->environ_v = ((char **)malloc(sizeof(char *) * info->env_count + 1));
	while (info->env_count > i)
	{
		start = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		len = ft_strlen(info->environ[i]);
		info->environ_v[i] = ft_strsub(info->environ[i], ++start, len);
		i++;
	}
}

static void	save_env_name(t_shell *info, int len, int i)
{
	info->environ_n = ((char **)malloc(sizeof(char *) * info->env_count + 1));
	while (info->env_count > i)
	{
		len = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		info->environ_n[i] = ft_strsub(info->environ[i], 0, len);
		i++;
	}
}

static void	split_path_variable(t_shell *info, int i)
{
	char	*var;

	while (!(ft_strequ(info->environ_n[i], "PATH")))
		i++;
	var = info->environ_v[i];
	info->split_path = ft_strsplit(var, ':');
	if (info->split_path == NULL)
		exit(EXIT_FAILURE);
}

void	store_environ_variables(t_shell *info, char **env)
{
	info->token = NULL;
	info->split_path = NULL;
	info->environ_n = NULL;
	info->environ_v = NULL;
	info->env_count = 0;
	allocate_envp(info, env);
	save_env_name(info, 0, 0);
	save_env_value(info, 0, 0);
	split_path_variable(info, 0);
}
