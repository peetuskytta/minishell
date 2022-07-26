/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 13:07:16 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/15 13:07:16 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_input_stdin(char *buf)
{
	int	bytes_read;

	ft_memset(buf, '\0', BUFFER);
	bytes_read = read(0, buf, BUFFER);
	if (bytes_read > 0 && bytes_read <= BUFFER)
		buf[bytes_read - 1] = '\0';
	else
		ft_putendl(CMD_TOO_LONG);
	//ft_putnbr_endl(bytes_read);
}

static void	clear_and_free_buffer(t_shell *data, char *string)
{
	int	index;

	index = search_var_name("_", data->environ_n, data);
	if (data->token_count == 1)
	{
		data->environ_v[index] = data->token[0];
		ft_memdel((void *)data->environ[index]);
		data->environ[index] = ft_strjoin(data->environ_n[index], data->token[0]);
	}
	else
		data->environ_v[i] = data->token[data->token_count];
	ft_memset(string, 0, ft_strlen(string));
	free(string);
}

static int	exit_and_clean(char *buf)
{
	if (ft_strequ(buf, EXIT) == TRUE)
	{
		ft_memset(buf, 0, ft_strlen(buf));
		free(buf);
		return (FALSE);
	}
	else
		return (TRUE);
}

static int	clear_env_or_empty(t_shell *data, char *buf)
{
	int	i;

	i = 0;
	if (ft_strequ(buf, CLEAR) == TRUE)
	{
		system("clear");
		return (TRUE);
	}
	else if (ft_strequ(buf, NOSTRING) == TRUE)
		return (TRUE);
	else if (ft_strequ(buf, ENV) == TRUE)
	{
		while (data->env_count > i)
			ft_putendl(data->environ[i++]);
		return (TRUE);
	}
	return (FALSE);
}

int	command_prompt_loop(t_shell *data)
{
	char	*buf;

	while (TRUE)
	{
		ft_putstr(PROMPT);
		buf = (char *)malloc(sizeof(char) * BUFFER);
		if (!buf)
			return (FALSE);
		read_input_stdin(buf);
		if (exit_and_clean(buf) == FALSE)
			return (FALSE);
		if (clear_env_or_empty(data, buf) == TRUE)
			clear_and_free_buffer(data, buf);
		else
		{
			parse_input(data, buf);
			clear_and_free_buffer(data, buf);
		}
	}
}
