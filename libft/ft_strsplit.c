/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:23:08 by pskytta           #+#    #+#             */
/*   Updated: 2022/06/21 11:49:19 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_word_size(char const *str, size_t i, char c)
{
	size_t	len;

	len = 0;
	while (str[i] == c)
		i++;
	while (str[i] != c && str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static int	ft_allocate_fill(char const *s, char **res, char c)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
			{
				res[k] = ft_strsub(s, i, ft_word_size(s, i, c));
				if (!res[k])
				{
					ft_free_array(k, res);
					return (0);
				}
				i = i + ft_word_size(s, i, c);
				k++;
			}
		}
	}
	return (1);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**result;
	int		ret;
	size_t	nbr;

	if (!s)
		ft_error_handler(2, "libft/ft_strsplit: empty string\n");
	nbr = ft_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!result)
		ft_error_handler(1, "libft/ft_strsplit <---\n");
	ret = ft_allocate_fill(s, result, c);
	if (ret)
		result[nbr] = 0;
	else
		result[nbr] = NULL;
	return (result);
}
