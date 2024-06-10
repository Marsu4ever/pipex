NAME = pipex

CFLAGS = -Wall -Wextra -Werror

SOURCES = 	accessory_functions.c\
			check_command_syntax.c\
			children.c\
			error_messages.c\
			find_path_to_executable.c\
			free_utils.c\
			initialize_struct.c\
			main.c\

LIBFT_DIR = ./libft

LIBFT = ./libft/libft.a

OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME) : $(OBJECTS) $(LIBFT)
	cc $(CFLAGS) $(OBJECTS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
