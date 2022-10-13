/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:03:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 13:22:00 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_if_quote(char c)
{
	return (c == S_QUOTE || c == D_QUOTE);
}

/*
**	This function is used to increment index and other counters in find_token
**	function. Uses int action to define which integers are to be modified.
*/
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
	{
		*count += 1;
		*i += 1;
	}
	else if (action == 6)
		to_init->at_end = TRUE;
}

static void	quote_check(t_ints *in, char *input, int *count, int *i)
{
	if (check_if_quote(input[*i]) == TRUE)
	{
		while (input[*i] == D_QUOTE && in->s_quo == FALSE)
			increment_counters(in, count, i, 2);
		while (input[*i] == S_QUOTE && in->d_quo == FALSE)
			increment_counters(in, count, i, 1);
		if (in->d_quo >= 2 || in->s_quo >= 2)
			increment_counters(in, count, i, 6);
	}
}

char	*find_token(char *input, char *token, int *count, int i)
{
	t_ints	in;

	ft_memset(&in, 0, sizeof(in));
	while (ft_is_ws_without_nl(input[i]))
		increment_counters(&in, count, &i, 5);
	while (input[i])
	{
		quote_check(&in, input, count, &i);
		if ((ft_is_ws_without_nl(input[i]) && in.at_end)
			|| (ft_is_ws_without_nl(input[i]) && in.s_quo + in.d_quo == FALSE))
		{
			increment_counters(&in, count, &i, 4);
			break ;
		}
		if ((input[i] != '\0' && in.at_end == FALSE)
			|| (!ft_is_ws_without_nl(input[i] && in.at_end == TRUE)))
		{
			token[in.pos++] = input[i++];
			increment_counters(&in, count, &i, 4);
		}
	}
	if (input[ft_strlen(token)] == '\0')
		return (NULL);
	return (token);
}

/*
**	Allocates memory for input containing quotes token at a time.
**	Keeps track of token count.
*/
void	tokenize_complex_input(t_shell *data, char *input, int index)
{
	char	*token;
	int		alloc_count;
	int		i;

	i = 0;
	data->token_count = -1;
	alloc_count = (int)ft_word_count(input, ' ') + 1;
	data->token = (char **)ft_memalloc(sizeof(char *) * alloc_count + 1);
	alloc_count = 0;
	while (input[i])
	{
		token = ft_strnew(ft_strlen(input));
		data->token[alloc_count] = find_token(input, token, &index, i);
		if (ft_strlen(data->token[alloc_count]) == 0 \
			&& data->token[alloc_count] != NULL)
			data->token[alloc_count][0] = '\0';
		if (data->token[alloc_count] == NULL)
			break ;
		i = index;
		alloc_count++;
		data->token_count++;
	}
}
