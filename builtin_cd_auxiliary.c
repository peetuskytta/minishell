/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_auxiliary.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 16:58:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/09 16:58:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_to_home_env(t_shell *data, int len, int home_i)
{
	char	*cur_dir;
	char	*buf;

	cur_dir = getcwd(data->pwd, 4096);
	if (search_var_name("OLDPWD", data) < 0)
		add_env_variable(data, "OLDPWD", cur_dir, data->env_count);
	else
		modify_env(data, "OLDPWD", cur_dir, 0);
	len = ft_strlen(data->environ[home_i]);
	buf = ft_strsub(data->environ[home_i], 5, len - 5);
	if (chdir(buf) != 0)
	{
		ft_memdel((void *)&(buf));
		return (TRUE);
	}
	ft_memdel((void *)&(buf));
	modify_env(data, "PWD", getcwd(data->pwd, 4096), 0);
	ft_memset(data->pwd, '\0', 4096);
	return (TRUE);
}

static void	modify_pwd(t_shell *data, char *name)
{
	ft_memset(data->pwd, '\0', 4096);
	getcwd(data->pwd, 4096);
	modify_env(data, name, data->pwd, 0);
}

int	handle_cd_dash(t_shell *data, int var_i, int len)
{
	char	*temp;

	var_i = search_var_name("OLDPWD", data);
	if (var_i > 0)
	{
		len = ft_strlen(data->environ[var_i]);
		temp = ft_strsub(data->environ[var_i], 7, len - 7);
		modify_pwd(data, "OLDPWD");
		if (chdir(temp) != 0)
		{
			free(temp);
			return (3);
		}
		if (search_var_name("PWD", data) < 0)
			add_env_variable(data, "PWD", temp, data->env_count);
		else
			modify_env(data, "PWD", temp, 0);
		ft_putendl(temp);
		free(temp);
	}
	else
		ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
	return (3);
}

int	handle_home(t_shell *data)
{
	int	count;
	int	home_index;

	count = data->env_count;
	reset_last_cmd_env(data, 0);
	home_index = search_var_name("HOME", data);
	if (home_index < 0)
	{
		error_print(MINISH, "cd:", CD_HOME_UNSET);
		return (TRUE);
	}
	if (search_var_name("PWD", data) < 0)
		add_env_variable(data, "PWD", getcwd(data->pwd, 4096), count);
	return (change_to_home_env(data, 0, home_index));
}

int	change_to_token(t_shell *data, const char *path)
{
	int	nbr;

	nbr = data->env_count;
	if (path)
	{
		if (search_var_name("OLDPWD", data) < 0)
			add_env_variable(data, "OLDPWD", getcwd(data->pwd, 4096), nbr);
		else
			modify_pwd(data, "OLDPWD");
		if (chdir(path) != 0)
		{
			error_print(CD_SH, (char *)path, NO_FILE_OR_DIR);
			return (TRUE);
		}
		getcwd(data->pwd, 4096);
		if (search_var_name("PWD", data) < 0)
			add_env_variable(data, "PWD", data->pwd, data->env_count);
		modify_env(data, "PWD", data->pwd, 0);
		return (TRUE);
	}
	return (TRUE);
}
