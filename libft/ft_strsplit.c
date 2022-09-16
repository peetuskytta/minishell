/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 13:23:08 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/16 16:47:24 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_size(char const *str, size_t i, char c)
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

static void	allocate_fill(char const *s, char **res, char c)
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
				res[k] = ft_strsub(s, i, word_size(s, i, c));
				i = i + word_size(s, i, c);
				k++;
			}
		}
	}
}

char	**ft_strsplit(char const *s, char c)
{
	char	**result;
	size_t	nbr;

	if (!s)
		return (NULL);
	nbr = ft_word_count(s, c);
	result = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (!result)
		exit(EXIT_FAILURE);
	allocate_fill(s, result, c);
	result[nbr] = NULL;
	return (result);
}
