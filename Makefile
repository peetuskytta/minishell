#Compiler and compiler flags
CC := gcc
#DEBUG_FLAGS := -g -fsanitize=address
FLAGS := -Wall -Wextra -Werror

#Color scheme
WHITE_BACKGROUND = \033[47m
VIOLET_BACKGROUND = \033[0;45m
YELLOW_BACKGROUND = \033[0;43m
WHITE = \033[37m
YELLOW = \033[33m
BLACK = \033[30m
VIOLET = \033[35m
RESET = \033[0m
RED = \033[31m
CYAN = \033[36m
BOLD = \033[1m

#Target Binary Program
NAME := minishell

SOURCES := main.c \
	read_input.c \
	store_environ.c \
	input_parser.c \
	builtin_unsetenv.c \
	builtin_echo.c \
	builtin_setenv_auxiliary.c \
	builtin_setenv_one_arg.c \
	builtin_setenv.c \
	builtin_cd.c \
	builtin_cd_auxiliary.c \
	execute_builtin.c \
	tokenize_simple_input.c \
	tokenize_complex_input.c \
	fork_and_exec.c \
	fork_and_exec_auxiliary.c \
	expand_input.c \
	error_handler.c \
	shell_history.c \
	special_purpose_functions.c \
	quotes.c \
	builtin_env.c \
	builtin_env_output.c \

OBJ := $(SOURCES:.c=.o)

LIBFT_M := make -s -C libft
LIBFT_A := libft/libft.a
HEADER := minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	@echo "$(BOLD)$(WHITE)$(NAME) Compilation done$(RESET)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@ -I includes/

$(LIBFT_A):
	@make -C libft/

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@echo "$(BOLD)$(RED)OBJ deleted$(RESET)"

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(BOLD)$(RED)$(NAME) deleted$(RESET)"

re: fclean all

.PHONY: all, clean, fclean, re