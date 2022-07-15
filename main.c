/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:26:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/07 09:26:07 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	data_initializer(t_shell *init)
{
	init->env_count = 0;
	init->var2 = 0;
	init->var3 = 0;
	while (environ[init->env_count] != NULL)
		init->env_count++;
}

int	main(int argc, char **argv, char **envp)
{

	t_shell	*data;

	if (argc && argv)
	{
		data = (t_shell *)malloc(sizeof(t_shell));
		data->environ = envp;
		data_initializer(data);
		write(1, "$>", 3);
	}
//	data->env = (char **)malloc(sizeof(char *) * count + 1);
//	data->env[count] = (char *)malloc(sizeof(char) * (len + 1));

	ft_putendl("The end. Thanks for using minishell.");
	return (0);
}