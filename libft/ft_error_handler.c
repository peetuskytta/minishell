/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 13:20:57 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/02 23:14:44 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_error_handler(int err_id, char *str)
{
	if (err_id == 1)
	{
		write(2, "---> malloc() failed in: ", 25);
		write(2, str, (int)ft_strlen(str));
		exit(EXIT_FAILURE);
	}
	if (err_id == 2)
	{
		write(2, "---> error: ", 12);
		write(2, str, (int)ft_strlen(str));
		exit(EXIT_FAILURE);
	}
}
