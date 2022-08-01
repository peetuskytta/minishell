CC := gcc
DEBUG_F := -g -fsanitize=address
FLAGS := -Wall -Wextra -Werror -g -fsanitize=address

NAME := minishell
SOURCES := main.c \
	read_input.c \
	store_environ.c \
	input_parser.c \
	builtin_unsetenv.c \
	builtin_setenv_auxiliary.c \
	builtin_setenv.c \
	builtin_cd.c \
	execute_command.c \
	tokenize_input.c \

OBJ := $(SOURCES:.c=.o)

LIBFT_M := make -s -C libft
LIBFT := libft/libft.a
HEADER := minishell.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "Compiling the $(NAME)"
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ): $(SOURCES) $(HEADER)
#	@echo "Creating $(NAME) object files"
	$(CC) $(FLAGS) -c $(SOURCES)

$(LIBFT):
	@make -s -C libft/

clean:
	@make -s -C libft clean
	@rm -f $(OBJ)
#	@echo "$(NAME) object files deleted"

fclean: clean
	@make -s -C libft fclean
	@rm -f $(NAME)
#	@echo "$(NAME) deleted"

re: fclean all

debug:
	@$(LIBFT_M)
	@$(CC) $(FLAGS) $(DEBUG_F) -c $(SOURCES)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME)

.PHONY: all clean fclean re debug