/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 12:32:36 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/02 12:32:36 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	output_environment(t_shell *data, int i)
{
	if (data->token_count == 0)
	{
		reset_last_cmd_env(data, data->last_cmd);
		while (data->env_count > i)
			ft_putendl(data->environ[i++]);
		return (TRUE);
	}
	else
	{
		reset_last_cmd_env(data, data->last_cmd);
		return (TRUE);
	}
}

static void	swap_char_ptr(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

static int	env_i_flag_error_check(char *executable, int err)
{
	if (ft_strequ(executable, "minishell") == 1)
		err = TRUE;
	else if (ft_strequ(executable, "./minishell") == 1)
		err = FALSE;
	else
		err = TRUE;
	return (err);
}

int	handle_env(t_shell *data, int error)
{
	if (data->token_count == 0)
		output_environment(data, 0);
	if (ft_strequ(data->token[1], "-i") == 1 && data->token[2])
	{
		error = env_i_flag_error_check(data->token[2], 0);
		data->env_i = (char **)ft_memalloc(sizeof(data->env_i));
		if (error == TRUE)
		{
			error_print("env: ", data->token[2], NO_FILE_OR_DIR);
			ft_memdel((void *)&(data->env_i));
			return (TRUE);
		}
		if (error == FALSE)
		{
			swap_char_ptr(&data->token[0], &data->token[2]);
			data->cmd = ft_strdup(data->token[0]);
			create_child_process(data, data->env_i);
		}
		ft_memdel((void *)&(data->env_i));
		ft_memdel((void *)&(data->cmd));
	}
	return (TRUE);
}
