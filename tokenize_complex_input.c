/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_complex_input.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pskytta <pskytta@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:12:21 by pskytta           #+#    #+#             */
/*   Updated: 2022/09/28 11:18:59 by pskytta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_complex_input(t_shell *data, char *input, int i)
{
	ft_putchar(NEWLINE);
	ft_putchar(NEWLINE);
	ft_putnbr_endl(data->quotes);
	i = 1;
	ft_putstr(input);
	exit(1);
}