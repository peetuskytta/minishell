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

//void	initialiser()

int	main(int argc, char **argv, char **envp)
{
	int	i = 0;
	int	count = 0;
	char new[5] = "VAR1";
	t_shell	*data;

	data = malloc(sizeof(t_shell));
	data->env = envp;
	while (data->env[i] != NULL)
	{
		ft_putendl(data->env[i]);
		i++;
	}
	count = i;
	

	envp[count] = ft_strdup(new);

	data->env = envp;
	i = 0;
	while (data->env[i] != NULL)
	{
		ft_putendl(data->env[i]);
		i++;
	}

	if (argc == 2 && ft_strcmp(argv[1], "minishell") == 0)
	{
		write(1, "$>", 3);
		while (1)
		{
			sleep(10);
			break;
		}
	}
	else
		ft_putendl("mistake");

	return (0);
}