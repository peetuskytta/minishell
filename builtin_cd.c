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
		ft_putstr(CD_NO_ACCESS);
		ft_putendl(name);
	}
	return (3);
}

static int	access_or_not(t_shell *data, const char *path)
{
	char	*temp;
	int		end;

	end = 0;
	temp = ft_strdup(path);
	if (temp[ft_strlen(temp)] != '/')
		ft_strcat((char *)temp, "/");
	while (TRUE)
	{
		end = (int)(ft_strrchr(temp, '/') - temp);
		if (end <= 0)
			break;
		temp = ft_strsub(temp, 0, end);
		if (access(temp, X_OK) == -1)
		{
			free((char *)temp);
			return(cd_error_message((char *)path, 2));
		}
	}
	if (ft_is_directory((char *)path) == 1)
		return (change_to_token(data, path));
	return (cd_error_message((char *)path, 1));
}
	/*
/Users/speedupeloton/Hive/projects/minishells
/Users/speedupeloton/Hive/projects/JOKU/OK/NOT_OK/DEF_NO_GO
	*/

static int initial_checks(t_shell *data)
{
	if (data->token[1] == NULL || data->token[1][0] == '\0')
		return (FALSE);
	if (ft_strequ(data->token[1], "-") == 1)
		return (handle_cd_dash(data, 0, 0));
	return (access_or_not(data, data->token[1]));
}

int	current_dir_actions(t_shell *data)
{
	int	checks;

	checks = initial_checks(data);
	if (checks == 1 && data->token[1] != NULL)
	{
		ft_putendl("success: token is a directory");
		reset_last_cmd_env(data, 0);
		return (change_current_directory(data));
	}
	if (checks == 0 && data->token[1] == NULL)
	{
		ft_putendl("change to $HOME directory");
		reset_last_cmd_env(data, 0);
		if (search_var_name("HOME", data) < 0)
			return (TRUE);
		return (change_current_directory(data));
	}
	if (checks == 3)
		return (TRUE);
	return (TRUE);
}

