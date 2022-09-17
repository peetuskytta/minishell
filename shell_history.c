/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/17 19:05:50 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function outputs the whole history to the stdout line by line.
*/
static void	output_history(int i, int fd)
{
	char	*line;

	line = NULL;
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

/*
**	Funtion finds a specific command from the history
*/
static void find_in_history(t_shell *data, int fd)
{
	char	*buf;
	char	**new_token;
	int		line_count;
	int		line_nbr;

	line_count = 1;
	new_token = NULL;
	buf = NULL;
	line_nbr = ft_atoi(data->token[0]);
	if (fd > 0)
	{
		while (line_count != line_nbr)
		{
			get_next_line(fd, &buf);
			free(buf);
			line_count++;
		}
		ft_memdel((void *)&data->token[0]);
		if (ft_strrchr(buf, WHITESPACE))
			data->token = ft_strsplit(buf, WHITESPACE);
		else
			data->token[0] = ft_strdup(buf);
		ft_memdel((void *)&(buf));
		close(fd);
	}
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
			ft_memdel((void *)&(buf));
		}
		if (data->token[0] != NULL)
			ft_free_arr_of_arrays(data->token);
		//else
		//	ft_memdel((void *)&(data->token[0]));
		if (ft_strrchr(buf, WHITESPACE))
			data->token = ft_strsplit(buf, WHITESPACE);
		else
			data->token[0] = ft_strdup(buf);
		ft_memdel((void *)&(buf));
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
			ft_memdel((void *)&(buf));
		}
	}
	close(fd);
}

void	handle_history(t_shell *data, int option)
{
	count_history(data, open(SH_HISTORY, O_RDONLY));
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
	else if (option == 2)
		last_in_history(data, open(SH_HISTORY, O_RDONLY));
	else if (option == 3)
		find_in_history(data, open(SH_HISTORY, O_RDONLY));
}