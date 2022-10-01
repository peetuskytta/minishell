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
	else if (ft_strchr(input, SINGLEQUOTE))
		return (FALSE);
	else if (ft_strchr(input, DOUBLEQUOTE))
		return (FALSE);
	else
		return (TRUE);
}

static char	*copy_squotes(char *token, int k)
{
	char	new[1024];
	int		i;

	i = 0;
	ft_memset(new, '\0', 1024);
	while (token[k] != '\0')
	{
		if (token[k] == SINGLEQUOTE)
			k++;
		if (token[k] == '\0')
			break;
		new[i] = token[k];
		k++;
		i++;
	}
	new[i] = '\0';
	//ft_putendl(new);
	return (ft_strcpy(new, new));
}

static char	*copy_dquotes(char *token, int k)
{
	char	new[1024];
	int		i;

	i = 0;
	ft_memset(new, '\0', 1024);
	while (token[k] != '\0')
	{
		if (token[k] == DOUBLEQUOTE)
			k++;
		if (token[k] == '\0')
			break;
		new[i] = token[k];
		k++;
		i++;
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
		if (ft_strchr(data->token[i], DOUBLEQUOTE))
		{
			ft_strcat(tmp, copy_dquotes(data->token[i], 0));
			ft_memdel((void *)&(data->token[i]));
			data->token[i] = ft_strdup(tmp);
			ft_memset(tmp, '\0', 1024);
			//ft_putendl(tmp);
			i++;
		}
		else if (ft_strchr(data->token[i], SINGLEQUOTE))
		{
			ft_strcat(tmp, copy_squotes(data->token[i], 0));
			ft_memdel((void *)&(data->token[i]));
			data->token[i] = ft_strdup(tmp);
			ft_memset(tmp, '\0', 1024);
			//ft_putendl(tmp);
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
		translate_quotes(data, 0);
	else
		check_expansion(data, 0);
	if (check_if_builtin(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else if (initial_exec_checks(data) == TRUE)
		reset_last_cmd_env(data, 0);
	else
		reset_last_cmd_env(data, 0);
	data->quotes = FALSE;
}
