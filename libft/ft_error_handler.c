/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:20:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/08/28 19:19:17 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_handler(int err_id, char *str)
{
	if (err_id == 1)
	{
		write(1, "---> malloc() failed in: ", 25);
		write(1, str, (int)ft_strlen(str));
		exit(1);
	}
	if (err_id == 2)
	{
		write(1, "---> error: ", 12);
		write(1, str, (int)ft_strlen(str));
		exit(0);
	}
}
