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

static void	expand_variable(int i, int var_i, t_shell *data)
{
	char	*temp;
	int		len;

	temp = ft_strsub(data->token[i], 1, ft_strlen(data->token[i] - 1));
	var_i = search_var_name(temp, data);
	ft_memdel((void *)&data->token[i]);
	if (var_i == -1)
		data->token[i] = ft_strdup("");
	else
	{
		len = ft_strlen(data->environ[var_i]) - ft_strlen(temp) + 1;
		data->token[i] = ft_strsub(data->environ[var_i], ft_strlen(temp) + 1, len);
	}
	free(temp);
}

static void	expand_home(int i, int var_i, t_shell *data)
{
	int		len;

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

static void	check_for_spaces(t_shell *data, char *input, int i)
{
	char	temp[4096];
	int		tok;
	int		inp_i;

	tok = 1;
	inp_i = 0;
	ft_memset(temp, '\0', 4096);
	while (input[i] != '\0')
	{
		if (input[i] == BACKSLASH)
			temp[inp_i] = input[++i];
		if (input[i + 1] == ' ')
		{
			temp[++inp_i] = '\0';
			data->token[tok] = ft_strdup(temp);
			ft_memset(temp, '\0', 4096);
			tok++;
		}
		temp[inp_i++] = input[i++];
	}
	temp[inp_i] = '\0';
	data->token[tok] = ft_strdup(temp);
}

int	tokenize_input(t_shell *data, char *input, int i)
{
	while (input[i++] != '\0')
	{
		if (ft_is_wspace(input[i]))
			input[i] = ' ';
	}
	if (ft_strchr(input, BACKSLASH))
		check_for_spaces(data, input, 0);
	else
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
