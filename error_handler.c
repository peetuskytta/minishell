/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 15:46:07 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/03 16:04:40 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error_print(char *sh, char *name, char *msg)
{
	ft_putstr(sh);
	ft_putstr(name);
	ft_putendl(msg);
}
