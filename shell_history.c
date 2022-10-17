/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 11:06:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/14 14:10:00 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
**	Drives the actions when history command is used.
*/
void	handle_history(int option)
{
	if (option == 1)
		output_history(1, open(SH_HISTORY, O_RDONLY));
}
