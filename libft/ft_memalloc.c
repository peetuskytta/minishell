/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 11:05:37 by pskytta           #+#    #+#             */
/*   Updated: 2022/10/12 15:57:39 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*ret;

	ret = (void *)malloc(size);
	if (ret == NULL)
	{
		ft_putstr_fd("\e[1;37mERROR: minishell: ", STDERR_FILENO);
		ft_putendl_fd("Cannot allocate memory.\033[0m", STDERR_FILENO);
		exit(111);
	}
	ft_memset(ret, '\0', size);
	return (ret);
}
