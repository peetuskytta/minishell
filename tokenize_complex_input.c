/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/06 11:58:28 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h> // REMEMBER TO DELETE

static int	check_if_quote(char c)
{
	return (c == S_QUOTE || c == D_QUOTE);
}

static void	increment_counters(t_ints *to_init, int *count, int *i, int action)
{
	if (action == 1)
	{
		to_init->s_quo += 1;
		*count += 1;
		*i += 1;
	}
	else if (action == 2)
	{
		to_init->d_quo += 1;
		*count += 1;
		*i += 1;
	}
	else if (action == 3)
		to_init->pos += 1;
	else if (action == 4)
		*count += 1;
	else if (action == 5)
		*i += 1;
	else if (action == 6)
		to_init->at_end = TRUE;

}


static char	*find_token(char *input, int *count, int i)
{
	char	*token;
	t_ints	in;

	ft_memset(&in, 0, sizeof(in));
	token = ft_strnew(ft_strlen(input));
	while (ft_is_ws_without_nl(input[i]) && (*count)++)
		increment_counters(&in, count, &i, 5);
	while (input[i])
	{
		if (check_if_quote(input[i]) == TRUE)
		{
			while (input[i] == D_QUOTE && in.s_quo == FALSE)
				increment_counters(&in, count, &i, 2);
			while (input[i] == S_QUOTE && in.d_quo == FALSE)
				increment_counters(&in, count, &i, 1);
			if (in.d_quo >= 2 || in.s_quo >= 2)
				increment_counters(&in, count, &i, 6);
		}
		if ((ft_is_ws_without_nl(input[i]) && in.at_end)
			|| (ft_is_ws_without_nl(input[i]) && in.s_quo + in.d_quo == FALSE))
		{
			increment_counters(&in, count, &i, 4);
			break ;
		}
		if ((input[i] && in.at_end == FALSE) || (!ft_is_ws_without_nl(input[i]
			&& in.at_end == TRUE)))
		{
			token[in.pos++] = input[i++];
			increment_counters(&in, count, &i, 4);
		}
	}
	if (input[ft_strlen(token) + 1] == '\0')
		return (NULL);
	return (token);
}


void	tokenize_complex_input(t_shell *data, char *input, int index)
{
	int	alloc_count;
	int	i;

	i = 0;
	alloc_count = (int)ft_word_count(input, ' ') + 1;
	data->token = (char **)ft_memalloc(sizeof(char *) * alloc_count + 1);
	alloc_count = 0;
	while (input[i])
	{
		data->token[alloc_count] = find_token(input, &index, i);
		//printf("token[%d]-->{%s}\n", alloc_count, data->token[alloc_count]);
		if (data->token[alloc_count] == NULL)
			break ;
		i = index;
		alloc_count++;
		data->token_count++;
	}
	printf("token count: %d\n", data->token_count);
}
