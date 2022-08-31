/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:09:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/31 11:37:00 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_variable(int i, int var_i, t_shell *data)
{
	char	*temp;
	int		len;
	int		w_len;

	temp = ft_strsub(data->token[i], 1, ft_strlen(data->token[i] - 1));
	w_len = ft_strlen(temp) + 1;
	var_i = search_var_name(temp, data);
	ft_memdel((void *)&data->token[i]);
	if (var_i == -1)
		data->token[i] = ft_strdup("");
	else
	{
		len = ft_strlen(data->environ[var_i]) - w_len;
		data->token[i] = ft_strsub(data->environ[var_i], w_len, len);
	}
	free(temp);
}

static void	expand_home(int i, int var_i, t_shell *data)
{
	int		len;
	// copy parts behind the tilde and join them back after expanding ~/Hive/projects

	var_i = search_var_name("HOME", data);
	if (var_i == -1)
	{
		ft_memdel((void *)&data->token[i]);
		data->token[i] = ft_strdup("");
	}
	else
	{
		ft_memdel((void *)&data->token[i]);
		len = ft_strlen(data->environ[var_i]);
		data->token[i] = ft_strsub(data->environ[var_i], 5, len);
	}
}

static void	expand_token(int id, int i, t_shell *data)
{
	int		var_i;

	var_i = 0;
	if (id == 1)
		expand_variable(i, var_i, data);
	if (id == 2)
		expand_home(i, var_i, data);
}

void	check_expansion(t_shell *data, int i)
{
	while (data->token[i] != NULL)
	{
		if (data->token[i][0] == '$')
			expand_token(1, i, data);
		else if (ft_strequ(data->token[i], "~") == TRUE)
			expand_token(2, i, data);
		i++;
	}
}
