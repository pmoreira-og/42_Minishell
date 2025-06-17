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
VAL = valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes \
	--track-origins=yes --trace-children=yes --suppressions=readline.supp

# === COMPILATION ===
CC = cc
CFLAGS =  -Wall -Werror -Wextra -I$(INCLUDES) -I$(LIBFT_DIR)/include -g
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
DIR_GENERAL = .
DIR_EXEC = exec
DIR_PARSE = parse
DIR_UTILS = utils

# === FILES ===
SRC_BUILT_INS = pwd.c cd.c echo.c env.c exit.c export.c unset.c

SRC_GENERAL = misc.c minishell.c env_manager.c export_manager.c executor.c

SRC_EXEC	= aux.c redirs.c child.c

SRC_PARSE =	tokenize.c ft_params.c checkers.c expand.c extra.c parser.c \
			literal.c commands.c utils.c aux.c errors.c ft_add_spaces.c \
			sub_list.c validators.c ft_quotes.c ft_redirs.c

SRC_UTILS =	cleaners.c constructors.c checkers.c printers.c aux_cleaners.c \
			aux_cleaners2.c signals.c

SRCS_DIR =	$(addprefix $(SRC)/, $(addprefix $(DIR_BUILT_INS)/, $(SRC_BUILT_INS))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_GENERAL)/, $(SRC_GENERAL))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_EXEC)/, $(SRC_EXEC))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_PARSE)/, $(SRC_PARSE))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_UTILS)/, $(SRC_UTILS)))

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

val: re
	$(VAL) ./minishell

debug: re
	$(VAL) ./minishell -d

.PHONY: all clean fclean re val debug
