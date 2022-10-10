/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:05:37 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/10 10:13:45 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ret;

	ret = (void *)malloc(size);
	if (ret == NULL)
	{
		ft_putstr_fd("\nminishell: ", STDERR_FILENO);
		ft_putendl_fd("Cannot allocate memory.", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}
