/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/12 10:23:40 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Creates the .minish_history file if it doesn't exist and appends the
**	command to the end of the file. File is created in the working
**	directory instead of the $HOME.
*/
void	create_or_append_history(char *buf)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(SH_HISTORY, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR \
	| S_IWUSR | S_IRWXU);
	while (ft_is_wspace(buf[i]))
		i++;
	if (fd > 0)
	{
		if (ft_strequ("!!", buf) != 1)
			ft_putendl_fd(buf + i, fd);
	}
	close(fd);
}

/*
**	Finds the last command executed from the history.
*/
static void	last_in_history(t_shell *data, int fd)
{
	char	*buf;
	int		i;

	i = 0;
	if (fd > 0)
	{
		while (get_next_line(fd, &buf) != 0)
		{
			if (i == data->h_index - 1)
				break ;
			i++;
			ft_memdel((void *)&(buf));
		}
		if (data->token)
			free_array(data->token);
		if (ft_strrchr(buf, D_QUOTE) || ft_strrchr(buf, S_QUOTE))
			tokenize_complex_input(data, buf, 0);
		else
			data->token = ft_strsplit(buf, WHITESPACE);
		ft_putendl_fd(buf, STDOUT_FILENO);
		ft_memdel((void *)&(buf));
		close(fd);
	}
}

/*
**	Get's the size of the history by counting the lines in the file.
*/
static void	count_history(t_shell *data, int fd)
{
	char	*buf;

	buf = NULL;
	data->h_index = 0;
	if (fd > 0)
	{
		while (get_next_line(fd, &buf) != 0)
		{
			data->h_index++;
			ft_memdel((void *)&(buf));
		}
	}
	if (fd > 0)
		close(fd);
}

/*
**	Drives the actions when history command is used.
*/
void	handle_history(t_shell *data, int option)
{
	count_history(data, open(SH_HISTORY, O_RDONLY));
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
	else if (option == 2)
		last_in_history(data, open(SH_HISTORY, O_RDONLY));
}
