/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:26:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/07 09:26:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_variable_counter(t_shell *info)
{
	while (info->environ[info->env_count] != NULL)
		info->env_count++;
}

static void	save_env_value(t_shell * info, int start, int i)
{
	info->environ_v = (char **)malloc(sizeof(char *) * info->env_count + 1);
	while (info->env_count > i)
	{
		start = (int)(ft_strchr(info->environ[i], '=') - info->environ[i]);
		info->environ_v[i] = ft_strsub(info->environ[i], ++start,
		ft_strlen(info->environ[i]));
		i++;
	}
	info->environ_v[i] = NULL;
}

static void	data_initializer(t_shell *info)
{
	info->env_count = 0;
	info->var1 = 0;
	info->var2 = 0;
	env_variable_counter(info);
	save_env_value(info, 0, 0);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	if (argc && argv)
	{
		data.environ = envp;
		data_initializer(&data);
		ft_putstr(CYAN"$> "DEF);
	}
	//ft_putendl(data.environ[0]);
	//ft_putendl(data.environ_v[0]);
	ft_putendl("");
	ft_putendl("The end. Thanks for using minishell.");
	return (0);
}