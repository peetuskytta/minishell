/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 19:10:31 by pskytta           #+#    #+#             */
/*   Updated: 2022/04/12 13:29:05 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnumber(long n, char *str, int *i)
{
	if (n > 9)
	{
		ft_putnumber(n / 10, str, i);
		ft_putnumber(n % 10, str, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	number;

	number = n;
	str = ft_memalloc(ft_nblen(number) + 1);
	i = 0;
	if (number < 0)
	{
		str[i++] = '-';
		number = number * -1;
	}
	ft_putnumber(number, str, &i);
	str[i] = '\0';
	return (str);
}
