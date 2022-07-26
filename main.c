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
		ft_memset(string[i], '\0', ft_strlen(string[i]));
		free(string[i]);
		i++;
	}
	free(string);
}

void	free_and_memset(t_shell *data, int i)
{
	free_double_ptr(data->split_path);
	while (data->env_count > i)
	{
		ft_memset(data->environ[i], '\0', ft_strlen(data->environ[i]));
		ft_memset(data->environ_n[i], '\0', ft_strlen(data->environ_n[i]));
		ft_memset(data->environ_v[i], '\0', ft_strlen(data->environ_v[i]));
		free(data->environ[i]);
		free(data->environ_n[i]);
		free(data->environ_v[i]);
		i++;
	}
	free(data->environ);
	free(data->environ_n);
	free(data->environ_v);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	if (argc && argv)
	{
		store_environ_variables(&data, envp);
		if (command_prompt_loop(&data) == FALSE)
			free_and_memset(&data, 0);
	}
	//free_double_ptr(data.token);
	exit(EXIT_SUCCESS);
}