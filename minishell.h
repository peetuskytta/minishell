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
# define CD_NOT_DIR "cd: not a directory: "
# define CD_NO_FILE_OR_DIR "cd: no such file or directory: "
# define MALLOC_FAIL "malloc failed: serious memory issues"
# define EMPTY_STR "setenv name: cannot be an empty string"
# define NAME_ERROR "setenv name: cannot be a NULL pointer or 0 length string"
# define STR_ILLEGAL_CHAR "setenv name: cannot include '='"
# define SETENV_USAGE "usage: setenv [name] [value]"
# define UNSETENV_USAGE "usage: unsetenv [name]"
# define SET_TOO_MANY_ARG "setenv: too many arguments\n"SETENV_USAGE
# define UNSET_TOO_MANY_ARG "unsetenv: too many arguments\n"UNSETENV_USAGE

/*Data structures used*/
typedef struct s_shell
{
	char	**environ;
	char	**split_path;
	char	**token;
	int		token_count;
	int		env_count;
	int		last_cmd;
}	t_shell;

void	store_environ_variables(t_shell *data, char **env);
void	parse_input(t_shell *data, char *input);
void	free_double_ptr(char **token);
void	free_and_memset(t_shell *data, int i);
void	execute_command(t_shell *data);
void	reset_env_value(t_shell *data, int i);
void	reset_last_cmd_env(t_shell *data, int var_i);
void	check_expansion(t_shell *data, int i);
void	modify_env(t_shell *data, char *name, char *value, int i);

void	add_env_variable(t_shell *data, char *name, char *str, int size);

int		change_current_directory(t_shell *data);

int		change_to_token(t_shell *data, const char *path);

int		handle_cd_dash(t_shell *data);

int		output_environment(t_shell *data, int i);
int		unset_error_check(t_shell *data);
int		command_prompt_loop(t_shell *data);
int		change_environ(t_shell *data, int id);
int		setenv_error_check(t_shell *data);
int		search_var_name(char *name, t_shell *data);
int		tokenize_input(t_shell *data, char *input, int i);
int		unset_env_variable(t_shell *data);
int		current_dir_actions(t_shell *data);

char	*join_n_and_v(char *name, char *value);


#endif
