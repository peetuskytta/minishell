/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/15 17:32:25 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	output_history(int i, int fd)
{
	char	*line;

	if (fd > 0)
	{
		while (get_next_line(fd, &line) == 1)
		{
			ft_putnbr(i++);
			ft_putstr("  ");
			ft_putendl(line);
			free(line);
		}
	}
	else
		ft_putendl("minishell: No history.");
	close(fd);
}

/*
**	Creates the .minish_history file if it doesn't exist and appends the
**	command to the end of the file.
*/
void	create_or_append_history(char *buf)
{
	int	fd;

	fd = open(SH_HISTORY, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR \
	| S_IWUSR | S_IRWXU);
	if (fd > 0)
	{
		if (ft_strequ("!!", buf) != 1)
			ft_putendl_fd(buf, fd);
	}
	close(fd);
}


static char **find_in_history(t_shell *data, int fd)
{
	char	**new_token;

	new_token = NULL;
	if (fd > 0)
	{
		close(fd);
	}
	ft_putnbr_endl(data->h_index);
	return (new_token);
}

static void	last_in_history(t_shell *data, int fd)
{
	char	*buf;
	int		i;

	i = 0;
	buf = NULL;
	if (fd > 0)
	{
		while (get_next_line(fd, &buf) != 0)
		{
			if (i == data->h_index - 1)
				break;
			i++;
			free(buf);
		}
		ft_memdel((void *)&data->token[0]);
		if (ft_strrchr(buf, WHITESPACE))
			data->token = ft_strsplit(buf, WHITESPACE);
		else
			data->token[0] = ft_strdup(buf);
		free(buf);
		close(fd);
	}
}

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
			free(buf);
		}
	}
	close(fd);
}

void	handle_history(t_shell *data, int option)
{
	char	**temp;

	temp = NULL;
	count_history(data, open(SH_HISTORY, O_RDONLY));
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
	else if (option == 2)
		last_in_history(data, open(SH_HISTORY, O_RDONLY));
	else if (option == 3)
		temp = find_in_history(data, open(SH_HISTORY, O_RDONLY));
	if (temp != NULL && option != 2)
		data->token = temp;
}