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

int	check_if_env_exists(t_shell *data, char *name)
{
	if (search_var_name(name, data) == -1)
		return (FALSE);
	else
		return (TRUE);
}

int	change_to_home_env(t_shell *data)
{
	char	*buf;
	int		var_i;
	int		len;

	var_i = search_var_name("HOME", data);
	if (var_i == -1)
		return (TRUE);
	if (search_var_name("OLDPWD", data) < 0)
		add_env_variable(data, "OLDPWD", getcwd(data->pwd, 4096), data->env_count);
	else
		modify_env(data, "OLDPWD", getcwd(data->pwd, 4096), 0);
	len = ft_strlen(data->environ[var_i]);
	buf = ft_strsub(data->environ[var_i], 5, len - 5);
	if (chdir(buf) != 0)
	{
		ft_putendl("-minishell: cd: not a valid directory");
		free(buf);
		return (TRUE);
	}
	free(buf);
	modify_env(data, "PWD", getcwd(data->pwd, 4096), 0);
	ft_memset(data->pwd, '\0', 4096);
	return (TRUE);
}

static void modify_pwd(t_shell *data, char *name)
{
	ft_memset(data->pwd, '\0', 4096);
	getcwd(data->pwd, 4096);
	modify_env(data, name, data->pwd, 0);
}

int	handle_cd_dash(t_shell *data, int var_i, int len)
{
	char	*temp;

	var_i = search_var_name("OLDPWD", data);
	if (var_i < 0)
	{
		ft_putendl("-minishell: cd: OLDPWD not set");
		return (3);
	}
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
	return (3);
}

int	change_to_token(t_shell *data, const char *path)
{
	if (path)
	{
		if (search_var_name("OLDPWD", data) < 0)
			add_env_variable(data, "OLDPWD", getcwd(data->pwd, 4096), data->env_count);
		else
			modify_pwd(data, "OLDPWD");
		if (chdir(path) != 0)
		{
			ft_putstr(CD_NO_FILE_OR_DIR);
			ft_putendl(path);
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
