/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/30 18:01:04 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_input_string(t_shell *data, char *input, int i)
{
	char	temp[1024];
	int		pos;
	int		ind;

	pos = 0;
	ind = 0;
	data->token = (char **)malloc(sizeof(char *) * 100);
	allocation_check(data->token);
	ft_memset(temp, '\0', 1024);
	ft_memset(data->token, 0, sizeof(data->token));
	while (input[pos] != '\0')
	{
		if (input[pos] == DOUBLEQUOTE)
		{
			while (input[++pos] != DOUBLEQUOTE)
				temp[ind++] = input[pos];
			if (ft_isalnum(input[++pos]))
			{
				while (!(ft_is_wspace(input[pos])))
					temp[ind++] = input[pos++];
				pos = ft_strlen(temp) + 2;
				while (ft_is_wspace(input[pos]))
					pos++;
			}
			ind = 0;
			data->token[i] = ft_strdup(temp);
			ft_memset(temp, '\0', 1024);
			i++;
		}
		temp[ind] = input[pos];
		ind++;
		pos++;
	}

	data->token[i] = NULL;
	data->token_count = i - 1;
	i = 0;
	while (data->token[i] != NULL)
	{
		ft_putnbr(i);
		ft_putstr("__");
		ft_putendl(data->token[i++]);
	}
	//exit(1);
}