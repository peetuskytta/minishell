/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:40:06 by pskytta           #+#    #+#             */
/*   Updated: 2021/12/14 11:20:54 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	j;
	char	*dest;
	char	*source;

	j = 0;
	dest = (char *)dst;
	source = (char *)src;
	while (j < n)
	{
		dest[j] = source[j];
		if ((unsigned char)source[j] == (unsigned char)c)
			return ((char *)dst + j + 1);
		j++;
	}
	return (NULL);
}
