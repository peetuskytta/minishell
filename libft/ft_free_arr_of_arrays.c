/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr_of_arrays.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:15:46 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/16 11:23:15 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_arr_of_arrays(char **string)
{
	int	i;

	i = 0;
	while (string[i] != NULL)
	{
		ft_memset(string[i], 0, ft_strlen(string[i]));
		free(string[i]);
		i++;
	}
	free(string);
}
