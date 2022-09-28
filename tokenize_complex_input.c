/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:12:21 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/28 20:09:16 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_to_tokens(char *string, char **tokens, int i)
{
	ft_putchar(NEWLINE);
	while (i < 100 && *string != '\0')
	{
		while (*string != '\0')
		{
			if (ft_is_wspace(*string + 1))
			{
				i++;
				break ;
			}
			*tokens[i] = *string;
			*string++;
		}
	}
 	if (i == 100)
		ft_putendl_fd("minishell: argument limit: 100", 2);
	ft_putchar(NEWLINE);
	tokens[i] = NULL;
}

void	tokenize_complex_input(t_shell *data, char *input, int i)
{
//	int	on[3];
	data->token = (char **)malloc(sizeof(char *) * (100));
	allocation_check(data->token);
	split_to_tokens(input, data->token, i);

	exit(1);
}
