/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_purpose_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/02 21:13:28 by pskytta          ###   ########.fr       */
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
			ft_putnbr_endl(size);
			cwd = ft_strnew(size);
		}
		else
			break ;
	}
	ft_memdel((void *)&(cwd));
	size *= 10;
	data->pwd_size = size;
	data->pwd = ft_strnew(size);
	getcwd(data->pwd, size);
}
