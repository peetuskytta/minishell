/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/15 12:09:33 by pskytta          ###   ########.fr       */
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

void	create_or_append_history(char *buf)
{
	int	fd;

	fd = open(SH_HISTORY, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR \
	| S_IWUSR | S_IRWXU);
	if (fd > 0)
	{
		ft_putendl_fd(buf, fd);
	}
	close(fd);
}

/*
static char *find_in_histyory(int fd)
{

}
*/

void	handle_history(t_shell *data, int option)
{
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
	else if (option == 2)
		ft_putendl("data->token[0] will be the last command");
	else if (option == 3)
		ft_putendl("data->token[0] will be the nth command from history specified by the digit after the ! character");
	data->h_index = 1;
}