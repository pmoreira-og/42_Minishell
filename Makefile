# === COLORS ===
RED=\033[1;31m
YELLOW=\033[1;33m
ORANGE=\033[1;38;5;214m
GREEN=\033[1;32m
CYAN=\033[1;36m
RESET=\033[0m

# === NAME ===
NAME = minishell

# === VALGRIND FLAGS ===
# valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=readline.supp

# === COMPILATION ===
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -I$(LIBFT_DIR)/include -g
OBJDIR = build

# === INCLUDES ===
INCLUDES = include/

# === LIBFT ===
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# === SRC PATH ===
SRC = src

# === MODULE DIRS ===
DIR_BUILT_INS = built_ins
DIR_FD = .
DIR_PIPEX = pipex
DIR_PARSE = parse

# === FILES ===
SRC_BUILT_INS = pwd.c cd.c echo.c env.c exit.c

SRC_FD = misc.c minishell.c env.c env_manager.c

SRC_PIPEX =	pipex.c aux.c utils.c ft_parse.c

SRC_PARSE =	first.c

SRC_NUM =	

SRC_STR =	

PRINTF =	

SRC_GNL =	

SRCS_DIR =	$(addprefix $(SRC)/, $(addprefix $(DIR_BUILT_INS)/, $(SRC_BUILT_INS))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_FD)/, $(SRC_FD))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_PIPEX)/, $(SRC_PIPEX))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_PARSE)/, $(SRC_PARSE))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_CHECK)/, $(SRC_CHECK))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_LISTS)/, $(SRC_LISTS))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_MEM)/, $(SRC_MEM))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_NUM)/, $(SRC_NUM))) \

OBJS_DIR = $(addprefix $(OBJDIR)/, $(SRCS_DIR:$(SRC)/%.c=%.o))

# === RULES ===
all: $(NAME)

$(NAME): $(OBJS_DIR) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_DIR) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)Done!$(RESET)"

$(LIBFT):
	@make -C $(LIBFT_DIR) -s

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(RED)Removing objects$(RESET)"
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR) -s

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_DIR) -s

re: fclean all
	@echo "$(ORANGE)Re-Done!!$(RESET)"

.PHONY: all clean fclean re
