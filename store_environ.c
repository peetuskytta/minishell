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

static void	env_variable_counter(t_shell *info)
{
	info->env_count = 0;
	while (info->environ[info->env_count] != NULL)
		info->env_count++;
}

static void	save_env_value(t_shell *info, int start, int i)
{
	info->environ_v = (char **)malloc(sizeof(char *) * info->env_count + 1);
	while (info->env_count > i)
	{
		start = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		info->environ_v[i] = ft_strsub(info->environ[i], ++start,
		ft_strlen(info->environ[i]));
		i++;
	}
}

static void	save_env_name(t_shell *info, int start, int i)
{
	info->environ_n = (char **)malloc(sizeof(char *) * info->env_count + 1);
	while (info->env_count > i)
	{
		start = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		info->environ_n[i] = ft_strsub(info->environ[i], 0, start);
		info->environ_n[i][start] = '\0';
		i++;
	}
}

void	store_environ_variables(t_shell *info)
{
	env_variable_counter(info);
	save_env_value(info, 0, 0);
	save_env_name(info, 0, 0);
}
