/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:51:54 by pskytta           #+#    #+#             */
/*   Updated: 2021/12/20 20:22:26 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	char	temp;
	int		i;
	int		k;

	i = 0;
	k = ft_strlen(str) - 1;
	while (i < k)
	{
		temp = str[i];
		str[i] = str[k];
		str[k] = temp;
		k--;
		i++;
	}
	return (str);
}
