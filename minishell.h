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

/*Builtin command defines*/
# define CD "cd"
# define ENV "env"
# define EXIT "exit"
# define ECHO "echo"
# define CLEAR "clear"
# define SETENV "setenv"
# define UNSETENV "unsetenv"

/*Other useful defines*/
# define CYAN "\033[0;36m"
# define DEFAULT "\033[0m"
# define PROMPT CYAN"$> "DEFAULT
# define NOSTRING ""
# define BACKSLASH '\\'
# define DOUBLEQUOTE '\"'
# define SINGLEQUOTE '\''
# define BUFFER 131072
# define EXIT_SUCCESS 0
# define FALSE 0
# define TRUE 1

/*Error message defines*/
# define CMD_TOO_LONG "command line argument is too long"
# define MALLOC_FAIL "malloc failed: serious memory issues"
# define EMPTY_STR "name: cannot be an empty string"
# define NULL_STR "name: cannot be a NULL pointer"
# define ZERO_LEN_STR "name: cannot be 0 length string"
# define STR_ILLEGAL_CHAR "name: cannot include '='"

/*Data structures used*/
typedef struct s_shell
{
	char	**environ;
	char	**environ_v;
	char	**environ_n;
	char	**split_path;
	char	**token;
	int		env_count;
}	t_shell;

void	store_environ_variables(t_shell *info);
int		command_prompt_loop(t_shell *data);
void	parse_input(t_shell *data, char *input);
void	free_double_ptr(char **token);
void	free_and_memset(t_shell *data, int i);
void	execute_command(t_shell *data);

int	change_environ(t_shell *data, int id);
int	setenv_name_error_check(t_shell *data);
int	search_var_name(char *name, char **name_array, t_shell *data);

#endif