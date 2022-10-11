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

/*
**	Updates the current directory and writes prompt to the stdout
*/
void	write_prompt_and_folder(t_shell *data)
{
	ft_memdel((void *)&(data->pwd));
	fetch_current_working_directory(data);
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putstr_fd(YELLOW, STDOUT_FILENO);
	ft_putstr_fd(data->pwd, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	ft_memdel((void *)&(data->pwd));
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	ft_memset(&data, 0, sizeof(data));
	data.token_count = -1;
	if (argc && argv)
	{
		store_environ_variables(&data, envp);
		if (command_prompt_loop(&data) == FALSE)
			exit(EXIT_SUCCESS);
	}
}
