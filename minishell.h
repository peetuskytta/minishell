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

# include "libft/libft.h"
# include <fcntl.h>

# if __linux__
#  include <sys/wait.h>
# endif

/*Builtin command defines*/
# define CD "cd"
# define ENV "env"
# define EXIT "exit"
# define ECHO "echo"
# define SETENV "setenv"
# define UNSETENV "unsetenv"
# define HISTORY "history"

/*Other useful defines*/
# define BLUE "\033[0;34m"
# define GREEN "\033[0;32m"
# define DEFAULT "\033[0m"

/*Other useful defines*/
# define PROMPT "minishell"
# define MINISH "minishell: "
# define SH_HISTORY ".minish_history"
# define NO_STRING ""
# define WHITESPACE ' '
# define TAB '\t'
# define NEWLINE '\n'
# define BACKSLASH '\\'
# define D_QUOTE '\"'
# define S_QUOTE '\''
# define EQUALSIGN "="
# define D_QUOTE_ARROW "dquote> "
# define S_QUOTE_ARROW "quote> "
# define ARROW "> "
# define TILDE '~'

/*Integer defines*/
# define BUFFER 4096
# define FALSE 0
# define TRUE 1

/*Error message defines*/
# define CMD_TOO_LONG "command line argument is too long"
# define MALLOC_FAIL "malloc failed: serious memory issues"
# define ARG_REQUIRED ": filename argument required"
# define ARG_USAGE_1 ": usage: "
# define ARG_USAGE_2 " filename [arguments]"
# define NO_FILE_OR_DIR ": No such file or directory"

/*Error message defines for CD*/
# define CD_SH "minishell: cd: "
# define CD_NO_ACCESS " permission denied"
# define CD_NOT_DIR ": Not a directory"
# define CD_HOME_UNSET " HOME not set"

/*Error message defines for setenv and unsetenv*/
# define EMPTY_STR "setenv name: cannot be an empty string"
# define NAME_ERROR "setenv name: cannot be a NULL pointer or 0 length string"
# define SETENV_USAGE "usage: 'setenv [name] [value]' or 'setenv [name=value]'"
# define UNSETENV_USAGE "usage: unsetenv [name]"
# define SET_TOO_MANY_ARG "setenv: too many arguments\n"
# define UNSET_TOO_MANY_ARG "unsetenv: too many arguments\n"
# define NOT_IDENTIFIER ": not a valid identifier"

/*Error messages for fork, waitpid, and execve*/
# define CMD_NOT_FOUND ": command not found"
# define EXEC_NO_ACCESS ": permission denied"
# define FORK_FAIL "minishell: fork fail"
# define WAITPID_FAIL "minishell: waitpid fail"
# define EXECVE_ERROR "minishell: error with execve"
# define IS_A_DIR ": is a directory"

/*Data structure(s) used*/
typedef struct s_shell
{
	char	**environ;
	char	**env_i;
	char	**split_path;
	char	**token;
	char	*cmd;
	char	*pwd;
	int		pwd_size;
	int		quotes;
	int		bytes;
	int		h_index;
	int		token_count;
	int		env_count;
	int		last_cmd;
	int		pid_status;
	int		no_nl;
}	t_shell;

void	store_environ_variables(t_shell *data, char **env);
void	parse_input(t_shell *data, char *input);
void	free_double_ptr(char **token);
void	free_and_memset(t_shell *data);
void	handle_command(t_shell *data);
void	reset_env_value(t_shell *data, int i);
void	reset_last_cmd_env(t_shell *data, int var_i);
void	check_expansion(t_shell *data, int i);
void	modify_env(t_shell *data, char *name, char *value, int i);
void	add_env_variable(t_shell *data, char *name, char *val, int size);
void	split_path_variable(t_shell *data, int i);

int		handle_env(t_shell *data, int error);
int		exec_error_check(t_shell *data, int check);
void	create_child_process(t_shell *data, char **env);
int		echo_driver(t_shell *data, int i);
void	cwd_size_check(t_shell *data, int size);
void	write_prompt_and_folder(t_shell *data);

void	error_print(char *sh, char *name, char *msg);
void	handle_history(t_shell *data, int option);
void	create_or_append_history(char *buf);
void	output_history(int i, int fd);
void	tokenize_simple_input(t_shell *data, char *input, int i);
void	add_only_name(t_shell *data, int var_i);
void	add_name_value(t_shell *data, int len, int i, int var_i);
void	allocation_check(void *to_check);
void	clean_input_string(t_shell *data, char *input, int i);

int		loop_path_variable(t_shell *data, char *temp, int i);
int		simple_input_check(char *input);
int		command_prompt_loop(t_shell *data);
int		exec_error_message(int id, char *name);
int		handle_home(t_shell *data);
int		check_if_builtin(t_shell *data);
int		check_if_env_exists(t_shell *data, char *name);
int		change_to_token(t_shell *data, const char *path);
int		handle_cd_dash(t_shell *data, int var_i, int len);
int		change_to_home_env(t_shell *data, int len, int var_i);
int		unset_error_check(t_shell *data);
int		change_environ(t_shell *data, int id);
int		setenv_error_check(t_shell *data);
int		search_var_name(char *name, t_shell *data);
int		unset_env_variable(t_shell *data);
int		current_dir_actions(t_shell *data);
int		initial_exec_checks(t_shell *data);

char	*join_n_and_v(char *name, char *value);
char	*handle_quotes(t_shell *data, char *old);
char	**allocate_last_in_history(char *buf);
char	*return_env_value(t_shell *data, char *name);

#endif
