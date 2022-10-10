/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 17:42:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 11:18:08 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	int		length;

	i = 0;
	if (!s1)
		ft_error_handler(2, "ft_strjoin: empty string\n");
	length = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = (char *)ft_memalloc(sizeof(char) * (length + 1));
	while (*s1)
		str[i++] = *s1++;
	while (*s2)
		str[i++] = *s2++;
	str[i] = '\0';
	return (str);
}
