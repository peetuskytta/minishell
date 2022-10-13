/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 10:19:00 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 08:57:17 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t	i;
	size_t	len;
	int		start;

	start = 0;
	i = 0;
	if (!s)
		return (NULL);
	while (ft_is_wspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(i));
	start = i;
	i = ft_strlen(s) - 1;
	while (ft_is_wspace(s[i]))
		i--;
	len = (i - start) + 1;
	return (ft_strsub(s, start, len));
}
