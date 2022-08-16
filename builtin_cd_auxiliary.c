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

static int	change_to_home_env(t_shell *data)
{
	char	home[4096];
	char	*buf;
	int		var_i;
	int		len;

	var_i = search_var_name("HOME", data);
	len = ft_strlen(data->environ[var_i]);
	buf = ft_strsub(data->environ[var_i], 5, len - 5);
	if (chdir(buf) != 0)
		ft_putendl("error in changing the directory (change_to_home_env");
	free(buf);
	modify_env(data, "PWD", getcwd(home, 4096), 0);
	getcwd(home, 4096);
	ft_putendl(home);
	return (TRUE);
}

static void modify_pwd(t_shell *data, char *name)
{
	char	buf[4096];

	ft_memset(buf, '\0', 4096);
	getcwd(buf, 4096);
	modify_env(data, name, buf, 0);
}

int	handle_cd_dash(t_shell *data)
{
	int		len;
	int		var_i;
	char	*temp;

	var_i = search_var_name("OLDPWD", data);
	if (var_i < 0)
		return (2);
	len = ft_strlen(data->environ[var_i]);
	temp = ft_strsub(data->environ[var_i], 7, len - 7);
	modify_pwd(data, "OLDPWD");
	if (chdir(temp) != 0)
	{
		free(temp);
		return (3);
	}
	modify_env(data, "PWD", temp, 0);
	free(temp);
	return (3);
}

int	change_to_token(t_shell *data, const char *path)
{
	char	pwd[4096];

	if (path)
	{
		modify_pwd(data, "OLDPWD");
		if (chdir(path) != 0)
		{
			ft_putstr(CD_NO_FILE_OR_DIR);
			ft_putendl(path);
			return (TRUE);
		}
		getcwd(pwd, 4096);
		modify_env(data, "PWD", pwd, 0);
		return (TRUE);
	}
	return (TRUE);
}

int	change_current_directory(t_shell *data)
{
	if (data->token[1] == NULL)
		return (change_to_home_env(data));
	else
	{
		if (search_var_name("OLDPWD", data) < 0)
			add_env_variable(data, "OLDPWD", "", data->token_count);
		return (change_to_token(data, NULL));
	}
}
