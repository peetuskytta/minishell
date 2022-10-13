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

static int	path_permission_loop(char **split, const char *path, int i)
{
	struct stat	stats;
	char		temp[4096];

	ft_memset(temp, '\0', 4096);
	while (TRUE)
	{
		if (split[i] == NULL)
			break ;
		if (temp[ft_strlen(temp)] != '/')
			ft_strcat(temp, "/");
		if (ft_strstr(split[i], ".."))
			ft_strcat(temp, split[i]);
		if (lstat(temp, &stats) == 0)
		{
			if (!(stats.st_mode & X_OK))
				return (cd_error_message((char *)path, 4));
		}
		else
			return (cd_error_message((char *)path, 2));
		if (temp[ft_strlen(temp)] != '/')
			ft_strcat(temp, "/");
		i++;
	}
	return (TRUE);
}

static int	check_access(t_shell *data)
{
	char	**split;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	if (ft_strchr(data->token[1], '/'))
	{
		split = ft_strsplit(data->token[1] + i, '/');
		ret = path_permission_loop(split, data->token[1], 0);
		free_array(split);
		if (ret == 3)
			return (3);
	}
	return (TRUE);
}

/*
**	First checks to define the continuation of the cd command. If it ends up
**	in the last line it will check the existence of the Path given.
*/
static int	initial_checks(t_shell *data)
{
	if (data->token[1] == NULL)
		return (FALSE);
	if (ft_strequ(data->token[1], "-") == 1)
		return (handle_cd_dash(data, 0, 0));
	if (ft_strequ(data->token[1], "~") == 1 || data->token[1] == NULL
		|| ft_strequ(data->token[1], "--") == 1 || data->token[1][0] == '\0')
		return (FALSE);
	return (check_access(data));
}

int	current_dir_actions(t_shell *data)
{
	int	checks;

	fetch_current_working_directory(data);
	check_expansion(data, 0);
	if (data->token_count < 2)
	{
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
	error_print(MINISH, "cd: ", "too many arguments");
	return (TRUE);
}
