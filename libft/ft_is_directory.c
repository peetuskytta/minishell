/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_directory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 22:10:49 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/21 22:10:49 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_directory(char *filename)
{
	struct stat	fileinfo;

	stat(filename, &fileinfo);
	return (S_ISDIR(fileinfo.st_mode));
}
