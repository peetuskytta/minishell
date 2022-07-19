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
	int	len;

	info->environ_v = (char **)malloc(sizeof(char *) * info->env_count + 1);
	while (info->env_count > i)
	{
		ft_strchr(info->environ[i], '=');
		info->environ_v[i] = ft_strdup(info->environ[i]);
		len = ft_strlen((info->environ[i]) - start);
		ft_putnbr_endl(len);
		//info->environ_v[i] = ft_strsub(info->environ[i], ++start, len);
		i++;
	}
	info->environ_v[info->env_count] = NULL;
}

static void	save_env_name(t_shell *info, int len, int i)
{
	info->environ_n = (char **)malloc(sizeof(char *) * info->env_count + 1);
	while (info->env_count > i)
	{
		len = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		info->environ_n[i] = ft_strsub(info->environ[i], 0, len);
		i++;
	}
	info->environ_n[i - 1] = NULL;
	ft_putendl(info->environ_n[23]);
}

static void	split_path_variable(t_shell *info, int i)
{
	char	*var;

	while (!(ft_strequ(info->environ_n[i], "PATH")))
		i++;
	var = info->environ_v[i];
	info->split_path = ft_strsplit(var, ':');
	/*i = 0;
	while (info->split_path[i] != NULL)
	{
		ft_putendl(info->split_path[i]);
		i++;
	}*/
}

void	store_environ_variables(t_shell *info)
{
	info->token = NULL;
	info->split_path = NULL;
	info->environ_n = NULL;
	info->environ_v = NULL;
	info->env_count = 0;
	env_variable_counter(info);
	save_env_value(info, 0, 0);
	save_env_name(info, 0, 0);
	split_path_variable(info, 0);
}
