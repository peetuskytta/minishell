/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:26:28 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/13 09:10:34 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", STDOUT_FILENO);
	else if (n < 0)
	{
		ft_putchar_fd('-', STDOUT_FILENO);
		ft_putnbr_fd(-n, STDOUT_FILENO);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, STDOUT_FILENO);
		ft_putchar_fd(n % 10 + '0', STDOUT_FILENO);
	}
	else
		ft_putchar_fd(n + '0', STDOUT_FILENO);
}
