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
# define BRED "\e[1;31m"
# define BBLU "\e[1;34m"
# define BWHT "\e[1;37m"
# define DEFAULT "\033[0m"

/*Other useful defines*/
# define PROMPT "minishell"
# define MINISH "minishell: "
# define SH_HISTORY ".minish_history"
# define NO_STRING ""
# define WHITESPACE ' '
# define NEWLINE '\n'
# define BACKSLASH '\\'
# define D_QUOTE '\"'
# define S_QUOTE '\''
# define EQUAL_SIGN "="
# define D_QUOTE_ARROW "dquote> "
# define S_QUOTE_ARROW "quote> "
# define TILDE '~'

/*Integer defines*/
# define BUFFER 1024
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
# define CD_HOME_UNSET " HOME not set"
# define CD_NO_ACCESS " permission denied"
# define CD_NOT_DIR ": Not a directory"
# define CD_SH "minishell: cd: "
# define IS_A_DIR ": Is a directory"

/*Error message defines for setenv and unsetenv*/
# define EMPTY_STR "setenv name: cannot be an empty string"
# define NAME_ERROR "setenv name: cannot be a NULL pointer or 0 length string"
# define SET_TOO_MANY_ARG "setenv: too many arguments"
# define SETENV_USAGE "usage: 'setenv [name] [value]'"
# define NOT_IDENTIFIER ": not a valid identifier"
# define UNSETENV_USAGE "usage: unsetenv [name]"
# define UNSET_TOO_MANY_ARG "unsetenv: too many arguments"
# define UNSETENV_TOO_LONG "unsetenv: argument too long"

/*Error messages for fork, waitpid, and execve*/
# define CMD_NOT_FOUND ": command not found"
# define EXEC_NO_ACCESS ": permission denied"
# define EXECVE_ERROR "minishell: error with execve"
# define FORK_FAIL "minishell: fork fail"
# define WAITPID_FAIL "minishell: waitpid fail"

/*Data structure(s) used*/
typedef struct s_shell
{
	char	**environ;
	char	**split_path;
	char	**env_i;
	char	**token;
	char	*cmd;
	char	*pwd;
	char	temp[8192];
	int		quotes;
	int		bytes;
	int		input_len;
	int		token_count;
	int		env_count;
	int		last_cmd;
	int		pid_status;
	int		no_nl;
}	t_shell;

typedef struct s_ints
{
	int	at_end;
	int	d_quo;
	int	s_quo;
	int	pos;
	int	index;
}	t_ints;

/*Prototypes*/
void	store_environ_variables(t_shell *data, char **env);
void	free_array(char **string);
void	free_and_memset(t_shell *data);
void	reset_last_cmd_env(t_shell *data, int var_i);
void	check_expansion(t_shell *data, int i);
void	modify_env(t_shell *data, char *name, char *value, int i);
void	add_env_variable(t_shell *data, char *name, char *val);
void	split_path_variable(t_shell *data, int i, int len);
void	create_child_process(t_shell *data, char **env);
void	fetch_current_working_directory(t_shell *data);
void	write_prompt_and_folder(t_shell *data);
void	tokenize_complex_input(t_shell *data, char *input, int i);
void	tokenize_simple_input(t_shell *data, char *input, int i);
void	error_print(char *sh, char *name, char *msg);
void	handle_history(int option);
void	create_or_append_history(char *buf);
void	output_history(int i, int fd);
void	add_only_name(t_shell *data, int var_i);
int		parse_input(t_shell *data, char *input);
int		handle_env(t_shell *data, int error);
int		exec_error_check(t_shell *data, int check);
int		echo_driver(t_shell *data, int i);
int		odd_nbr_of_quotes(char *buf, int *quotes);
int		check_if_builtin(t_shell *data);
int		simple_input_check(char *input);
int		command_prompt_loop(t_shell *data);
int		exec_error_message(int id, char *name);
int		handle_home(t_shell *data);
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
int		loop_path_variable(t_shell *data, char *temp, int i);
int		cd_error_message(char *name, int id);
int		output_environment(t_shell *data, int i);
char	*join_n_and_v(char *name, char *value);
char	*handle_open_quotes(t_shell *data, char *old, int *quotes);
char	*strjoin_free(char *s1, char *s2);

#endif
