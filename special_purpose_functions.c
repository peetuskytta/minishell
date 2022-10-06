/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_purpose_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/06 16:05:45 by pskytta          ###   ########.fr       */
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
	fetch_working_directory(data);
	ft_putstr_fd(GREEN, STDOUT_FILENO);
	ft_putstr_fd(PROMPT, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	ft_putchar_fd(':', STDOUT_FILENO);
	ft_putstr_fd(BLUE, STDOUT_FILENO);
	ft_putstr_fd(data->pwd, STDOUT_FILENO);
	ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	ft_putstr_fd("$ ", STDOUT_FILENO);
	ft_memdel((void *)&(data->pwd));
}

/*
**	This function gets the current workind directory and makes sure enough
**	space has been allocated for it by doubling the size after each
**	failed attempt of getcwd() function. In the end 10 times more space
**	is allocated to make sure there's enough space for concatenation.
*/
void	fetch_working_directory(t_shell *data)
{
	char	*cwd;

	ft_memdel((void *)&(data->pwd));
	cwd = getcwd(NULL, 0);
	data->pwd = ft_strdup(cwd);
	ft_memdel((void *)&(cwd));
}
