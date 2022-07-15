/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:02:33 by pskytta           #+#    #+#             */
/*   Updated: 2021/12/11 15:26:25 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p;

	p = (char *)s;
	if (c == '\0')
	{
		return ((char *)p + ft_strlen(p));
	}	
	while (p && *p)
	{
		if (*p == c)
		{
			return ((char *)p);
		}
		p++;
	}
	return (NULL);
}
