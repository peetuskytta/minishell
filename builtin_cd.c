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
	if (id == 3)
		return (3);
	return (3);
}

static int	path_permission_loop(char **split, const char *path)
{
	struct stat	stats;
	char		temp[4096];
	int			i;

	i = 0;
	ft_memset(temp, '\0', 4096);
	ft_strcat(temp, "/");
	while (TRUE)
	{
		if (split[i] == NULL)
			break ;
		ft_strcat(temp, split[i]);
		if (lstat(temp, &stats) == 0)
		{
			if (!(stats.st_mode & X_OK))
				return (cd_error_message((char *)path, 2));
		}
		ft_strcat(temp, "/");
		i++;
	}
	return (TRUE);
}

static int	check_access(t_shell *data)
{
	char	**split;
	int		ret;

	ret = 0;
	check_expansion(data, 0);
	if (ft_strchr(data->token[1], '/'))
	{
		split = ft_strsplit(data->token[1], '/');
		ret = path_permission_loop(split, data->token[1]);
		free_double_ptr(split);
		if (ret == 3)
			return (3);
	}
	return (TRUE);
}
	/*
/Users/speedupeloton/Hive/projects/minishell
/Users/speedupeloton/Hive/projects/JOKU/OK/NOT_OK/DEF_NO_GO
	*/

static int	initial_checks(t_shell *data)
{
	if (data->token[1] == NULL || data->token[1][0] == '\0')
		return (FALSE);
	if (ft_strequ(data->token[1], "-") == 1)
		return (handle_cd_dash(data, 0, 0));
	if (ft_strequ(data->token[1], "~") == 1 || data->token[1] == NULL
		|| ft_strequ(data->token[1], "--") == 1)
		return (FALSE);
	return (check_access(data));
}

int	current_dir_actions(t_shell *data)
{
	int	checks;

	check_expansion(data, 0);
	checks = initial_checks(data);
	if (checks == 1)
	{
		reset_last_cmd_env(data, 0);
		return (change_to_token(data, data->token[1]));
	}
	if (checks == 0)
		return (handle_home(data));
	if (checks == 3)
		return (TRUE);
	return (TRUE);
}
