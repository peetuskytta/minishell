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
# define EQUALSIGN "="
# define BUFFER 131072
# define FALSE 0
# define TRUE 1

/*Error message defines*/
# define CMD_TOO_LONG "command line argument is too long"
# define MALLOC_FAIL "malloc failed: serious memory issues"
# define EMPTY_STR "setenv name: cannot be an empty string"
# define NAME_ERROR "setenv name: cannot be a NULL pointer or 0 length string"
# define STR_ILLEGAL_CHAR "setenv name: cannot include '='"
# define SETENV_USAGE "usage: setenv [name] [value]"

/*Data structures used*/
typedef struct s_shell
{
	char	**environ;
	char	**split_path;
	char	**token;
	int		token_count;
	int		env_count;
	int		under;
}	t_shell;

void	store_environ_variables(t_shell *data, char **env);
void	parse_input(t_shell *data, char *input);
void	free_double_ptr(char **token);
void	free_and_memset(t_shell *data, int i);
void	execute_command(t_shell *data);
void	reset_env_value(t_shell *data, int i);
void	reset_last_cmd_env(t_shell *data);

int		command_prompt_loop(t_shell *data);
int		change_environ(t_shell *data, int id);
int		setenv_name_error_check(t_shell *data);
int		search_var_name(char *name, t_shell *data);

char	*join_n_and_v(char *name, char *value);

#endif