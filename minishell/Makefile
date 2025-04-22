# Caminhos
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
BUILT_INS = ./built_ins

# sources
SRC = minishell.c misc.c $(BUILT_INS)/echo.c $(BUILT_INS)/pwd.c $(BUILT_INS)/cd.c

# Flags
CFLAGS = -Wall -Wextra -Werror -I$(LIBFT_DIR)

# Compilação
OBJS = $(SRC:.c=.o)
NAME = minishell

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
