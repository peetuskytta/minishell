/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 09:26:23 by pskytta           #+#    #+#             */
/*   Updated: 2022/07/07 09:26:23 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include "libft/libft.h"

# define EXIT "exit"
# define CYAN "\033[0;36m"
# define DEF "\033[0m"

typedef struct s_shell
{
	char	**environ;
	char	**environ_v;
	int		env_count;
	int		var1;
	int		var2;
}	t_shell;

//void	data_initializer(t_shell *init);

#endif