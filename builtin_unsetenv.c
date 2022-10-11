/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:27:09 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/22 07:27:09 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_variable(char **strings, int var_i, int count)
{
	while (count > var_i)
	{
		ft_memdel((void *)&(strings[var_i]));
		strings[var_i] = ft_strdup(strings[var_i + 1]);
		var_i++;
	}
	ft_memdel((void *)&(strings[var_i]));
}

int	unset_error_check(t_shell *data)
{
	if (ft_strequ(data->token[0], UNSETENV) == TRUE)
	{
		if (data->token_count == 1)
			return (TRUE);
		if (data->token_count > 1)
			ft_putendl_fd(UNSET_TOO_MANY_ARG, 2);
		if (ft_strlen(data->token[1]) > BUFFER)
			ft_putendl_fd(UNSETENV_TOO_LONG, 2);
		else
			ft_putendl_fd(UNSETENV_USAGE, 2);
	}
	return (FALSE);
}

int	unset_env_variable(t_shell *data)
{
	int		var_i;
	int		i;

	i = 0;
	if (data->token_count == 1)
	{
		var_i = search_var_name(data->token[1], data);
		if (var_i < 0)
			return (TRUE);
		remove_variable(data->environ, var_i, data->env_count - 1);
		data->env_count = i;
		while (data->environ[i++] != NULL)
			data->env_count++;
		return (TRUE);
	}
	else
	{
		ft_putendl_fd(UNSETENV_USAGE, 2);
		return (FALSE);
	}
}
