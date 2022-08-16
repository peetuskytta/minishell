/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 22:03:24 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/01 22:03:24 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if tokens?
// check for -L or -P flags?
// check for -
// check for /
// check for .. and .
//

static int	check_access_permission(t_shell *data, const char *path)
{
//	char	**split;
	char	*temp;
//	int		i;
	int		var_i;

	var_i = search_var_name("OLDPWD", data);
	if (var_i < 0)
		add_env_variable(data, "OLDPWD", "", data->env_count);
	if (ft_strequ(path, "-") == TRUE)
	{
		temp = ft_strsub(data->environ[var_i], 8, ft_strlen(data->environ[var_i]) - 8);
		if (change_to_token(data, temp) == TRUE)
			modify_env(data, "OLDPWD", temp, 0);
		free(temp);
		return (TRUE);
	}
//	i = 0;
//	split = ft_strsplit(path, '/');
//	while (split[i] != NULL)
//		ft_putendl(split[i++]);
//	ft_free_array(i, split);
	return (change_to_token(data, path));
}

static int	cd_error_message(char *name, int id)
{
	if (id == 1)
	{
		if (!name)
			ft_putstr(CD_NO_FILE_OR_DIR);
		else
		{
			ft_putstr(CD_NO_FILE_OR_DIR);
			ft_putendl(name);
		}
	}
	if (id == 2)
	{
		ft_putstr(CD_NOT_DIR);
		ft_putendl(name);
	}
	return (FALSE);
}

static int initial_checks(t_shell *data)
{
	int	ret;

	if (data->token[1] == NULL)
		return (FALSE);
	if (ft_strequ(data->token[1], "-") == 1)
		return (handle_cd_dash(data));
	ret = ft_is_directory(data->token[1]);
	ft_putnbr_endl(ret);
	if (ret == -1)
		return (cd_error_message(data->token[1], 1));
	else if (ret == 1)
		return (check_access_permission(data, data->token[1]));
	else
		return (cd_error_message(data->token[1], 2));
}

int	current_dir_actions(t_shell *data)
{
	int	checks;

	checks = initial_checks(data);
	if (checks == 1 && data->token[1] != NULL)
	{
		ft_putendl("success: token is a directory");
		reset_last_cmd_env(data, data->last_cmd);
		return (change_current_directory(data));
	}
	if (checks == 0 && data->token[1] == NULL)
	{
		ft_putendl("change to $HOME directory");
		reset_last_cmd_env(data, data->last_cmd);
		return (change_current_directory(data));
	}
	if (checks == 2)
		ft_putendl("-minishell: cd: OLDPWD not set");
	if (checks == 3)
		return (change_current_directory(data));
	return (TRUE);
}

