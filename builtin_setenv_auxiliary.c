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
**	ft_strjoin exits if malloc fails
*/
char	*join_n_and_v(char *name, char *value)
{
	char	temp[4096];

	ft_memset(temp, '\0', 4096);
	ft_strcat(temp, name);
	ft_strcat(temp, EQUALSIGN);
	name = temp;
	return (ft_strjoin(name, value));
}

void	reset_last_cmd_env(t_shell *data, int var_i)
{
	int	index;

	index = data->token_count;
	var_i = search_var_name("_", data);
	if (var_i == -1)
	{
		add_env_variable(data, "_", "", data->env_count);
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
