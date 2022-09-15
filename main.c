/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:26:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/07 09:26:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		ft_memset(string[i], 0, ft_strlen(string[i]));
		free(string[i]);
		i++;
	}
	free(string);
}

/*
void	free_and_memset(t_shell *data)
{
	if (data->cmd != NULL)
		free(data->cmd);
	free_double_ptr(data->split_path);
	free_double_ptr(data->environ);
	if (data->token != NULL)
		free_double_ptr(data->token);
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	ft_memset(&data, 0, sizeof(data));
	data.token_count = -1;
	if (argc && argv)
	{
		store_environ_variables(&data, envp);
		if (command_prompt_loop(&data) == FALSE)
		{
			exit(EXIT_SUCCESS);
		}
	}
}
