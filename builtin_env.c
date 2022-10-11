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

static void	swap_char_ptr(char **first, char **second)
{
	char	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

static int	count_env_number(char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != NULL)
	{
		if (ft_strchr(str[i++], '='))
			count++;
	}
	return (count);
}

static void	send_to_execute(t_shell *new, t_shell *data)
{
	new->cmd = ft_strdup(new->temp);
	new->token[0] = ft_strdup(data->token[0]);
	create_child_process(new, new->env_i);
	ft_memdel((void *)&(new->cmd));
	free_array(new->token);
	free_array(new->env_i);
}

static void	work_env_i(t_shell *data, int i, int k, int count)
{
	t_shell	new;

	ft_memset(&new, 0, sizeof(new));
	ft_memcpy(&new, data, sizeof(t_shell));
	count = count_env_number(new.token);
	new.env_i = (char **)ft_memalloc(sizeof(char *) * (count + 1));
	new.token = (char **)ft_memalloc(sizeof(char *) * (data->token_count + 1));
	while (new.token[i] != NULL)
	{
		new.token[i] = ft_strdup(data->token[i]);
		if (ft_strchr(new.token[i], '='))
			new.env_i[k++] = ft_strdup(new.token[i]);
		i++;
	}
	new.env_i[k] = NULL;
	k = 1;
	swap_char_ptr(&new.token[0], &new.token[data->token_count]);
	while (new.token[k] != NULL)
		ft_memdel((void *)&(new.token[k++]));
	send_to_execute(&new, data);
}

int	handle_env(t_shell *data, int error)
{
	if (data->token_count == 0)
		output_environment(data, 0);
	if (data->token_count >= 2)
	{
		if (error == FALSE && ft_strequ(data->token[1], "-i") == 1 \
			&& data->token[2] != NULL)
		{
			swap_char_ptr(&data->token[0], &data->token[data->token_count]);
			if (loop_path_variable(data, ft_strcat(data->temp, "/"), 0) == TRUE)
				work_env_i(data, 0, 0, 0);
			swap_char_ptr(&data->token[data->token_count], &data->token[0]);
		}
		else
			error_print("env: ", data->token[2], NO_FILE_OR_DIR);
	}
	ft_memdel((void *)&(data->cmd));
	return (TRUE);
}
