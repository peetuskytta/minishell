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
			error_print(CD_SH, name, NO_FILE_OR_DIR);
		else
			error_print(CD_SH, name, NO_FILE_OR_DIR);
	}
	else if (id == 2)
		error_print(CD_SH, name, NO_FILE_OR_DIR);
	else if (id == 3)
		return (3);
	else if (id == 4)
		error_print(CD_SH, name, CD_NO_ACCESS);
	return (3);
}

static int	path_permission_loop(char **split, const char *path)
{
	struct stat	stats;
	char		temp[4096];
	int			i;

	i = 0;
	ft_memset(temp, '\0', 4096);
	while (TRUE)
	{
		if (split[i] == NULL)
			break ;
		ft_strcat(temp, "/");
		ft_strcat(temp, split[i]);
		ft_putendl(temp);
		if (lstat(temp, &stats) == 0)
		{
			if (!(stats.st_mode & X_OK))
				return (cd_error_message((char *)path, 4));
		}
		else
			return (cd_error_message((char *)path, 2));
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
	check_expansion(data, 0);
	if (ft_strchr(data->token[1], '/'))
	{
		if (data->token[1][0] == '.')
			i++;
		split = ft_strsplit(data->token[1] + i, '/');
		ret = path_permission_loop(split, data->token[1]);
		ft_free_arr_of_arrays(split);
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
