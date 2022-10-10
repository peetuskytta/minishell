/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_exec_auxiliary.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:21:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 13:44:58 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	loop_path_variable(t_shell *data, char *temp, int i)
{
	int	var_i;

	var_i = search_var_name("PATH", data);
	if (var_i > 0)
		split_path_variable(data, 0);
	if (data->split_path == NULL)
		return (FALSE);
	while (data->split_path[i] != NULL)
	{
		ft_strcpy(temp, data->split_path[i]);
		ft_strcat(temp, "/");
		ft_strcat(temp, data->token[0]);
		if (access(temp, F_OK) == 0)
		{
			data->cmd = ft_strdup(temp);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}
