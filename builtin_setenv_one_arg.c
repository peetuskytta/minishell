/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv_one_arg.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 14:23:51 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/19 18:39:31 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_err_check(char *token, int i)
{
	while (ft_is_wspace(token[i]))
		i++;
	if (token[i] == '=' || ft_isdigit(token[i]))
	{
		ft_putstr(MINISH);
		error_print("setenv: ", token, NOT_IDENTIFIER);
		return (FALSE);
	}
	return (TRUE);
}

static int	setenv_handle_single_argument(t_shell *data, int i, int len)
{
	int		end;
	int		var_i;
	char	*name;
	char	*value;

	if (single_err_check(data->token[1], 0) == FALSE)
		return (FALSE);
	while (ft_is_wspace(data->token[1][i]))
		i++;
	if (!(ft_strchr(data->token[1], '=')))
	{
		var_i = search_var_name(data->token[1], data);
		if (var_i >= 0)
			modify_env(data, data->token[1], "", 0);
		else
			add_env_variable(data, data->token[1], "", data->env_count);
	}
	else
	{
		len = ft_strchr(data->token[1], '=') - data->token[1];
		name = ft_strsub(data->token[1], i, len);
		end = ft_strlen(data->token[1]) - ft_strlen(name);
		value = ft_strsub(data->token[1], len + 1, end);
		var_i = search_var_name(name, data);
		if (var_i > 0)
			modify_env(data, name, value, 0);
		else
			add_env_variable(data, name, value, data->env_count);
		ft_memdel((void *)&(name));
		ft_memdel((void *)&(value));
	}
	return (FALSE);
}

int	setenv_error_check(t_shell *data)
{
	if (ft_strequ(data->token[0], SETENV) == TRUE)
	{
		if (data->token_count == 1)
			return (setenv_handle_single_argument(data, 0, 0));
		if (data->token_count == 2)
		{
			if (ft_strchr(data->token[1], '=')
				|| ft_isdigit(data->token[1][0]))
			{
				ft_putstr(MINISH);
				error_print("setenv: ", data->token[1], NOT_IDENTIFIER);
				return (FALSE);
			}
			else
				return (TRUE);
		}
		else if (data->token_count > 2)
			ft_putendl(SET_TOO_MANY_ARG);
		return (FALSE);
	}
	else
		return (FALSE);
}
