/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:01:26 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/28 20:06:25 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	ptr = ft_strnew(len);
	if (!ptr)
		exit(EXIT_FAILURE);
	if (!s || start > ft_strlen(s))
		ft_error_handler(2, "libft/ft_strsub: empty string or index problem\n");
	ptr = ft_strncpy(ptr, (const char *)s + start, len);
	ptr[len] = '\0';
	return (ptr);
}
