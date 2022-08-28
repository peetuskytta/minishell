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
# define PROMPT CYAN"minishell> "DEFAULT
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

/*Error message defines for CD*/
# define CD_NO_ACCESS "cd: permission denied: "
# define CD_NO_FILE_OR_DIR "cd: no such file or directory: "

/*Error message defines for setenv and unsetenv*/
# define EMPTY_STR "setenv name: cannot be an empty string"
# define NAME_ERROR "setenv name: cannot be a NULL pointer or 0 length string"
# define STR_ILLEGAL_CHAR "setenv name: cannot include '='"
# define SETENV_USAGE "usage: setenv [name] [value]"
# define UNSETENV_USAGE "usage: unsetenv [name]"
# define SET_TOO_MANY_ARG "setenv: too many arguments\n"SETENV_USAGE
# define UNSET_TOO_MANY_ARG "unsetenv: too many arguments\n"UNSETENV_USAGE

/*Error messages for fork, waitpid, and execve*/
# define CMD_NOT_FOUND "minishell: command not found: "
# define EXEC_NO_ACCESS "minishell: permission denied: "
# define FORK_FAIL "minishell: fork error"
# define WAITPID_FAIL "minishell: waitpid fail"
# define EXECVE_ERROR "minishell: error with execve"

/*Data structures used*/
typedef struct s_shell
{
	char	**environ;
	char	**split_path;
	char	**token;
	char	*cmd;
	int		token_count;
	int		env_count;
	int		last_cmd;
	int		pid_status;
	char	pwd[4096];
}	t_shell;

void	store_environ_variables(t_shell *data, char **env);
void	parse_input(t_shell *data, char *input);
void	free_double_ptr(char **token);
void	free_and_memset(t_shell *data, int i);
void	handle_command(t_shell *data);
void	reset_env_value(t_shell *data, int i);
void	reset_last_cmd_env(t_shell *data, int var_i);
void	check_expansion(t_shell *data, int i);
void	modify_env(t_shell *data, char *name, char *value, int i);
void	create_child_process(t_shell *data);
void	add_env_variable(t_shell *data, char *name, char *val, int size);

int		check_if_builtin(t_shell *data);
int		check_if_env_exists(t_shell *data, char *name);
int		change_to_token(t_shell *data, const char *path);
int		handle_cd_dash(t_shell *data, int var_i, int len);
int		change_to_home_env(t_shell *data);
int		output_environment(t_shell *data, int i);
int		unset_error_check(t_shell *data);
int		command_prompt_loop(t_shell *data);
int		change_environ(t_shell *data, int id);
int		setenv_error_check(t_shell *data);
int		search_var_name(char *name, t_shell *data);
int		tokenize_input(t_shell *data, char *input, int i);
int		unset_env_variable(t_shell *data);
int		current_dir_actions(t_shell *data);
int		initial_exec_checks(t_shell *data);

char	*join_n_and_v(char *name, char *value);


#endif
