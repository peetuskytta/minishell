/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_purpose_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:47:10 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/11 13:52:13 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	adds the data->token[1] to the environment but doesnt set the value of it.
*/
void	add_only_name(t_shell *data, int var_i)
{
	if (var_i >= 0)
		modify_env(data, data->token[1], "", 0);
	else
		add_env_variable(data, data->token[1], "", data->env_count);
}

/*
**	Frees array of strings and sets pointer to null.
*/
void	free_array(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		if (string[i])
			ft_memset(string[i], 0, ft_strlen(string[i]));
		ft_memdel((void *)&(string[i]));
		i++;
	}
	ft_memdel((void *)&(string));
}

/*
**	Updates the current directory and writes prompt to the stdout
*/
void	write_prompt_and_folder(t_shell *data)
{
	ft_memdel((void *)&(data->pwd));
	fetch_current_working_directory(data);
	ft_putstr_fd(GREEN, 1);
	ft_putstr_fd(PROMPT, 1);
	ft_putstr_fd(DEFAULT, 1);
	ft_putchar_fd(':', 1);
	ft_putstr_fd(YELLOW, 1);
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
void	fetch_current_working_directory(t_shell *data)
{
	char	*cwd;

	ft_memdel((void *)&(data->pwd));
	cwd = getcwd(NULL, 0);
	data->pwd = ft_strdup(cwd);
	ft_memdel((void *)&(cwd));
}

/*
**	Joins two strings together and returning a new pointer to joined strings
**	
*/
char	*strjoin_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	ft_strcat(tmp, s1);
	ft_strcat(tmp, s2);
	ft_memdel((void *)&(s1));
	ft_memdel((void *)&(s2));
	return (tmp);
}
