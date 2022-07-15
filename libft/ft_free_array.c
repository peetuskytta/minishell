/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 17:28:49 by pskytta           #+#    #+#             */
/*   Updated: 2022/01/03 15:10:15 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(int nbr, char **res)
{
	while (nbr >= 0)
	{
		if (res[nbr] != NULL)
		{
			ft_bzero(res[nbr], ft_strlen(res[nbr]));
			ft_memdel((void **)res);
		}
		nbr--;
	}
	free(res);
}
