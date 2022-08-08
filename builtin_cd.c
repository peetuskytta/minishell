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

static int	check_access_permission(const char *path)
{
	ft_putendl(path);
	return (TRUE);
}

static int initial_checks(char *dirpath)
{
	int	ret;

	ret = ft_is_directory(dirpath);
	if (ret == -1)
	{
		write(1, CD_NO_FILE_OR_DIR, 34);
		ft_putendl(dirpath);
		return (FALSE);
	}
	else if (ret == 1)
		return (check_access_permission(dirpath));
	else
	{
		write(1, CD_NOT_DIR, 22);
		ft_putendl(dirpath);
	}
	return (FALSE);
}

int	change_cur_dir(t_shell *data)
{
	if (initial_checks(data->token[1]) == TRUE && data->token_count == 1)
	{
		ft_putendl("success");
		reset_last_cmd_env(data, data->last_cmd);
		return (TRUE);
	}
	else if (data->token_count != 1)
		ft_putendl("not enough tokens...");
	reset_last_cmd_env(data, data->last_cmd);
	return (TRUE);
}

