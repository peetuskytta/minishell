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

static void	create_or_append_history(char **history)
{
	int	i;
	int	fd;
	char	c;

	c = '\n';
	i = 1;
	fd = open(".minish_history", O_CREAT | O_RDWR | O_APPEND, S_IRUSR \
	| S_IWUSR | S_IRWXU);
	if (fd > 0)
	{
		while (history[i] != NULL)
		{
			write(fd, history[i], ft_strlen(history[i]));
			write(fd, &c, 1);
			i++;
		}
	}
	close(fd);
}

static void	copy_history(t_shell *data)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(".minish_history", O_RDONLY);
	if (fd > 0)
	{
		while (get_next_line(fd, &data->history[i]) == 1)
			i++;
		data->h_index = i;
		ft_putnbr_endl(data->h_index);
		close(fd);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	ft_memset(&data, 0, sizeof(data));
	data.token_count = -1;
	if (argc && argv)
	{
		copy_history(&data);
		store_environ_variables(&data, envp);
		if (command_prompt_loop(&data) == FALSE)
		{
			create_or_append_history(data.history);
			exit(EXIT_SUCCESS);
		}
	}
}
