/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 22:52:45 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/16 22:52:45 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_input_check(char *input)
{
	if (ft_strchr(input, BACKSLASH))
		return (FALSE);
	else if (ft_strchr(input, S_QUOTE))
		return (FALSE);
	else if (ft_strchr(input, D_QUOTE))
		return (FALSE);
	else
		return (TRUE);
}

static char	*copy_squotes(char *token, int k, int i)
{
	char	new[1024];

	ft_putendl(token);
	ft_memset(new, '\0', 1024);
	while (token[k] != '\0')
	{
		if (token[k] == S_QUOTE)
			k++;
		if (token[k] == '\0')
			break;
		else
			new[i++] = token[k++];
	}
	new[i] = '\0';
	ft_putendl(new);
	return (ft_strcpy(new, new));
}

static char	*copy_dquotes(char *token, int k, int i)
{
	char	new[1024];

	ft_memset(new, '\0', 1024);
	while (token[k] != '\0')
	{
		if (token[k] == D_QUOTE)
			k++;
		if (token[k + 1] == '\0')
			break;
		else
			new[i++] = token[k++];
	}
	new[i] = '\0';
	//ft_putendl(new);
	return (ft_strcpy(new, new));
}

static void	translate_quotes(t_shell *data, int i)
{
	char	tmp[1024];

	ft_memset(tmp, '\0', 1024);
	while (data->token[i] != NULL)
	{
		if (ft_strchr(data->token[i], D_QUOTE))
		{
			ft_strcat(tmp, copy_dquotes(data->token[i], 0, 0));
			ft_memdel((void *)&(data->token[i]));
			data->token[i] = ft_strdup(tmp);
			ft_putendl(tmp);
			ft_memset(tmp, '\0', 1024);
			i++;
		}
		else if (ft_strchr(data->token[i], S_QUOTE))
		{
			ft_strcat(tmp, copy_squotes(data->token[i], 0, 0));
			ft_memdel((void *)&(data->token[i]));
			data->token[i] = ft_strdup(tmp);
			ft_putendl(tmp);
			ft_memset(tmp, '\0', 1024);
			i++;
		}
		else
			i++;
		// memdel token and reassign with tmp
	}
}

void	parse_input(t_shell *data, char *input)
{
	tokenize_simple_input(data, input, 0);
	if (data->quotes == TRUE)
	{
		translate_quotes(data, 0);
		exit(1);
	}
	else
		check_expansion(data, 0);
	if (check_if_builtin(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else if (initial_exec_checks(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else
		reset_last_cmd_env(data, 0);
	ft_memdel((void *)&(data->pwd));
	data->quotes = FALSE;
}
