/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:18:34 by pskytta           #+#    #+#             */
/*   Updated: 2021/12/20 17:23:13 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*mydest;
	const char	*mysource;

	if ((dst == NULL) && (src == NULL))
		return (NULL);
	mydest = (char *)dst;
	mysource = (const char *)src;
	while (n > 0)
	{
		*mydest++ = *mysource++;
		n--;
	}
	return (dst);
}
