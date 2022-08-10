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

	ft_memset(home, '\0', 4096);
	getcwd(home, 4096);
	ft_putstr("before: ");
	ft_putendl(home);
	ft_memset(home, '\0', 4096);
	var_i = search_var_name("HOME", data);
	len = ft_strlen(data->environ[var_i]);
	buf = ft_strsub(data->environ[var_i], 5, len - 5);
	if (chdir(buf) != 0)
		ft_putendl("error in changing the directory");
	free(buf);
	ft_memset(home, '\0', 4096);
	getcwd(home, 4096);
	ft_putstr("after: ");
	ft_putendl(home);
	return (TRUE);
}

static int	change_to_token(t_shell *data)
{
	ft_putendl(data->token[1]);
	return (TRUE);
}

int	change_current_directory(t_shell *data)
{
	if (data->token[1] == NULL)
		return (change_to_home_env(data));
	else
	{
		return (change_to_token(data));
	}
}
