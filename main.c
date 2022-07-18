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

static void	cleanup_before_exit(t_shell *data, int i)
{
	while (data->env_count > i)
	{
		ft_memset(data->environ_n[i], '\0', ft_strlen(data->environ_n[i]));
		ft_memset(data->environ_v[i], '\0', ft_strlen(data->environ_v[i]));
		free(data->environ_n[i]);
		free(data->environ_v[i]);
		i++;
	}
	free(data->environ_n);
	free(data->environ_v);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	if (argc && argv)
	{
		data.environ = envp;
		store_environ_variables(&data);
		if (command_prompt_loop(&data) == false)
			cleanup_before_exit(&data, 0);
	}
	exit(EXIT_SUCCESS);
}