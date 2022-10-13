/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 17:43:22 by pskytta          ###   ########.fr       */
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
**	Drives the actions when history command is used. Options is in
**	here for future expansion.
*/
void	handle_history(t_shell *data, int option)
{
	count_history(data, open(SH_HISTORY, O_RDONLY));
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
}
