/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_purpose_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/03 08:42:28 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_last_in_history(char *buf)
{
	char	**new;

	new = (char **)malloc(sizeof(char *) * (1 + 1));
	allocation_check(new);
	new[0] = ft_strdup(buf);
	new[1] = NULL;
	return (new);
}

void	add_only_name(t_shell *data, int var_i)
{
	if (var_i >= 0)
		modify_env(data, data->token[1], "", 0);
	else
		add_env_variable(data, data->token[1], "", data->env_count);
}

void	allocation_check(void *to_check)
{
	if (!to_check)
		exit(EXIT_FAILURE);
}

/*
**	Updates the current directory and writes prompt to the stdout
*/
void	write_prompt_and_folder(t_shell *data)
{
	cwd_size_check(data, 255);
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd(PROMPT, 1);
	ft_putstr_fd(DEFAULT, 1);
	ft_putchar_fd(':', 1);
	ft_putstr_fd(BLUE, 1);
	ft_putstr_fd(data->pwd, 1);
	ft_putstr_fd(DEFAULT, 1);
	ft_putstr_fd("$ ", 1);
	ft_memdel((void *)&(data->pwd));
}

/*
**	This function gets the current workind directory and makes sure enough
**	space has been allocated for it by doubling the size after each
**	failed attempt of getcwd() function. In the end 10 times more space
**	is allocated to make sure there's enough space for concatenation.
*/
void	cwd_size_check(t_shell *data, int size)
{
	char	*cwd;

	cwd = ft_strnew(size);
	while (TRUE)
	{
		if (getcwd(cwd, size) == NULL)
		{
			ft_memdel((void *)&(cwd));
			size += size;
			cwd = ft_strnew(size);
		}
		else
			break ;
	}
	ft_memdel((void *)&(cwd));
	size *= 10;
	if (size >= 10000)
		size /= 2;
	data->pwd_size = size;
	data->pwd = ft_strnew(size);
	getcwd(data->pwd, size);
}
