/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 13:48:47 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/18 19:30:09 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (len == 0)
		return (dst);
	while (len--)
	{
		if (!(*src))
			dst[i] = '\0';
		else
		{
			dst[i] = *src;
			src++;
		}
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
