/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin_auxiliary.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:53:27 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/21 15:53:27 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Searches the NAME in the environment variables and returns the index of it.
**	used to check if variable exists in the environment.
*/
int	search_var_name(char *name, t_shell *data)
{
	char	*temp;
	int		len;
	int		i;

	i = 0;
	len = 0;
	temp = NULL;
	while (data->env_count > i)
	{
		len = (int)(ft_strchr(data->environ[i], '=') - data->environ[i]);
		temp = ft_strsub(data->environ[i], 0, len);
		if (ft_strequ(temp, name) == TRUE)
		{
			ft_memdel((void *)&temp);
			return (i);
		}
		ft_memdel((void *)&temp);
		i++;
	}
	return (-1);
}

/*
**	Returns the name and value joined.
*/
char	*join_n_and_v(char *name, char *value)
{
	char	temp[8192];

	ft_memset(temp, '\0', 8192);
	ft_strcat(temp, name);
	ft_strcat(temp, EQUAL_SIGN);
	name = temp;
	return (ft_strjoin(name, value));
}

/*
**	Resets the value of the environment variable _ (underscore) to be the last
**	argument of the command given as input.
*/
void	reset_last_cmd_env(t_shell *data, int var_i)
{
	int	index;

	index = data->token_count;
	var_i = search_var_name("_", data);
	if (var_i == -1)
	{
		add_env_variable(data, "_", "");
		var_i = search_var_name("_", data);
	}
	if (var_i >= 0)
		ft_memdel((void *)&data->environ[var_i]);
	if (data->token_count == 0)
		data->environ[var_i] = join_n_and_v("_", data->token[0]);
	else if (data->token_count == 1)
		data->environ[var_i] = join_n_and_v("_", data->token[1]);
	else if (data->token_count == 2)
		data->environ[var_i] = join_n_and_v("_", data->token[2]);
	else
		data->environ[var_i] = join_n_and_v("_", data->token[index]);
}
