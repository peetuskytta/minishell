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

static int	access_or_not(t_shell *data, const char *path)
{
	int		var_i;

	//if (check_permission(data, path) == TRUE)
	var_i = search_var_name("OLDPWD", data);
	if (var_i < 0)
		add_env_variable(data, "OLDPWD", "", data->env_count);
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

	if (data->token[1] == NULL || data->token[1][0] == '\0')
		return (FALSE);
	if (ft_strequ(data->token[1], "-") == 1)
		return (handle_cd_dash(data));
	ret = ft_is_directory(data->token[1]);
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
		//ft_putendl("success: token is a directory");
		reset_last_cmd_env(data, 0);
		return (change_current_directory(data));
	}
	if (checks == 0 && data->token[1] == NULL)
	{
		//ft_putendl("change to $HOME directory");
		reset_last_cmd_env(data, 0);
		if (search_var_name("HOME", data) < 0)
			return (TRUE);
		return (change_current_directory(data));
	}
	if (checks == 2)
		ft_putendl("-minishell: cd: OLDPWD not set");
	if (checks == 3)
		return (TRUE);
	//return (change_current_directory(data));
	return (TRUE);
}

