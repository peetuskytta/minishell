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

static int	check_access_permission(t_shell *data, const char *path)
{
	

	ft_putendl(data->token[0]);
	ft_putendl(path);
	return (TRUE);
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
	if (initial_checks(data) == TRUE && data->token[1] != NULL)
	{
		ft_putendl("success");
		reset_last_cmd_env(data, data->last_cmd);
		return (TRUE);
	}
	else
	{
		//ft_putendl("change to $HOME directory");
		reset_last_cmd_env(data, data->last_cmd);
		return (change_current_directory(data));
	}
	return (TRUE);
}

