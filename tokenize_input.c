/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:33:30 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/01 11:33:30 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_token(int id, int i, t_shell *data)
{
	int		len;
	int		var_i;
	char	*temp;

	var_i = 0;
	if (id == 2)
	{
		ft_memdel((void *)&data->token[i]);
		var_i = search_var_name("HOME", data);
		len = ft_strlen(data->environ[var_i] - 5);
		data->token[i] = ft_strsub(data->environ[var_i], 5, len);
	}
	if (id == 1)
	{
		temp = ft_strsub(data->token[i], 1, ft_strlen(data->token[i] - 1));
		ft_memdel((void *)&data->token[i]);
		var_i = search_var_name(temp, data);
		len = ft_strlen(data->environ[var_i]) - ft_strlen(temp) + 1;
		data->token[i] = ft_strsub(data->environ[var_i], ft_strlen(temp) + 1, len);
		free(temp);
	}
}

int	tokenize_input(t_shell *data, char *input, int i)
{
	while (input[i++] != '\0')
	{
		if (ft_is_wspace(input[i]))
			input[i] = ' ';
	}
	data->token = ft_strsplit(input, ' ');
	i = 0;
	while (data->token[i++] != NULL)
		data->token_count++;
	check_expansion(data, 0);
	return (TRUE);
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
