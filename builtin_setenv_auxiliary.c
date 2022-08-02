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

int	setenv_error_check(t_shell *data)
{
	if (data->token_count == 2)
	{
		if (data->token[1] == NULL || ft_strlen(data->token[1]) == 0)
			ft_putendl(NAME_ERROR);
		else if (ft_strchr(data->token[1], '='))
		{
			ft_putendl(STR_ILLEGAL_CHAR);
			return (FALSE);
		}
		else
			return (TRUE);
	}
	else if (data->token_count == 1 && ft_strchr(data->token[1], '='))
		ft_putendl(STR_ILLEGAL_CHAR);
	else if (data->token_count > 2)
		ft_putendl(TOO_MANY_ARG);
	return (FALSE);
}

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
			free(temp);
			return (i);
		}
		ft_memdel((void *)&temp);
		i++;
	}
	return (-1);
}

void	write_env(t_shell *data, int i)
{
	while (data->env_count > i)
	{
		if (data->environ[i][0] != '\0')
			ft_putendl(data->environ[i]);
		i++;
	}
}

/*
**	ft_strjoin exits if malloc fails
*/
char	*join_n_and_v(char *name, char *value)
{
	char	temp[1024];

	ft_memset(temp, '\0', ft_strlen(temp));
	ft_strcat(temp, name);
	ft_strcat(temp, EQUALSIGN);
	name = temp;
	return (ft_strjoin(name, value));
}

void	reset_last_cmd_env(t_shell *data)
{
	int	index;

	index = data->token_count;
	data->under = search_var_name("_", data);
	ft_memdel((void *)&data->environ[data->under]);
	if (data->token_count == 0)
		data->environ[data->under] = join_n_and_v("_", data->token[0]);
	else if (data->token_count == 1)
		data->environ[data->under] = join_n_and_v("_", data->token[1]);
	else if (data->token_count == 2)
		data->environ[data->under] = join_n_and_v("_", data->token[2]);
	else
		data->environ[data->under] = join_n_and_v("_", data->token[index]);
}
