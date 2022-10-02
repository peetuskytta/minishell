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

/*static void	swap_char_star(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}
*/
int	handle_env(t_shell *data)
{
	if (data->token_count == 0)
		output_environment(data, 0);
	if (ft_strequ(data->token[1], "-i") == 1 && data->token[2])
	{
		data->env_i = (char **)ft_memalloc(sizeof(data->env_i));
		if (!(ft_strnstr(data->token[2], "./", 2)))
		{
			ft_memdel((void *)&(data->env_i));
			return(FALSE);
		}
		data->cmd = ft_strdup(data->token[2]);
		create_child_process(data, data->env_i);
		ft_memdel((void *)&(data->env_i));
		ft_memdel((void *)&(data->cmd));
	}
	return (TRUE);
}