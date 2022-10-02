/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr_of_arrays.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:15:46 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/02 22:52:49 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr_of_arrays(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		if (string[i])
			ft_memset(string[i], 0, ft_strlen(string[i]));
		ft_memdel((void *)&(string[i]));
		i++;
	}
	ft_memdel((void *)&(string));
}
