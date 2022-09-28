/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_purpose_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/28 18:43:41 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_last_in_history(char *buf)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (1 + 1));
	if (!new)
		exit(EXIT_FAILURE);
	new[0] = ft_strdup(buf);
	new[1] = NULL;
	return (new);
}

void	add_only_name(t_shell *data, int var_i)
{
	if (var_i >= 0)
		modify_env(data, data->token[1], "", 0);
	else
		add_env_variable(data, data->token[1], "", data->env_count);
}

void	allocation_check(void *to_check)
{
	if (!to_check)
		exit(EXIT_FAILURE);
}
