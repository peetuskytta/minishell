/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:20:16 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/16 12:27:05 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Writes all the environment variables to the STDOUT.
*/
int	output_environment(t_shell *data, int i)
{
	if (data->token_count == 0)
	{
		reset_last_cmd_env(data, data->last_cmd);
		while (data->environ[i] != NULL)
			ft_putendl_fd(data->environ[i++], STDOUT_FILENO);
		return (TRUE);
	}
	else
	{
		reset_last_cmd_env(data, data->last_cmd);
		return (TRUE);
	}
}
