/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 10:38:02 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 09:03:10 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	i;
	char			*str;

	if (!s)
		ft_error_handler(STDERR_FILENO, "libft/ft_strmap: empty string\n");
	i = 0;
	str = ft_strnew(ft_strlen(s));
	if (str == NULL)
		ft_error_handler(STDERR_FILENO, "libft/ft_strmap <---\n");
	while (s[i] != '\0')
	{
		str[i] = f(s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
