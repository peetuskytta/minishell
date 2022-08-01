/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 07:27:09 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/22 07:27:09 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_env_variable(t_shell *data)
{
	int		var_i;
	int		len;

	if (data->token_count == 1)
	{
		var_i = search_var_name(data->token[1], data);
		len = ft_strlen(data->environ[var_i]);
		if (var_i > 0)
			ft_memset(data->environ[var_i], '\0', len);
		return (TRUE);
	}
	else
	{
		ft_putendl(SETENV_USAGE);
		return (FALSE);
	}
}
