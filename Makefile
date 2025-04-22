RED=\033[1;31m
YELLOW = \033[1;33m
ORANGE = \033[1;38;5;214m
GREEN = \033[1;32m
CYAN = \033[1;36m
RESET = \033[0m

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -lreadline
OBJDIR = build
INCLUDES = include/
INCLUDES_FLAGS = -I$(INCLUDES)

SRC = src
#MAIN = src/minishell.c

# Dirs
DIR_BUILT_INS = built_ins
DIR_FD = .
DIR_LISTS = ft_list
DIR_MEM = ft_memory
DIR_NUM = ft_num
DIR_STR = ft_strings
DIR_PRINTF = ft_printf
DIR_GNL = gnl

SRC_BUILT_INS =	pwd.c cd.c echo.c

SRC_FD =	misc.c minishell.c

SRC_LISTS =	

SRC_MEM =	

SRC_NUM =	

SRC_STR =	

PRINTF =	

SRC_GNL =	

SRCS_DIR =	$(addprefix $(SRC)/, $(addprefix $(DIR_BUILT_INS)/, $(SRC_BUILT_INS))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_FD)/, $(SRC_FD))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_GNL)/, $(SRC_GNL))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_STR)/, $(SRC_STR))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_CHECK)/, $(SRC_CHECK))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_LISTS)/, $(SRC_LISTS))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_MEM)/, $(SRC_MEM))) \
			#$(addprefix $(SRC)/, $(addprefix $(DIR_NUM)/, $(SRC_NUM))) \

OBJS_DIR = $(addprefix $(OBJDIR)/, $(SRCS_DIR:$(SRC)/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS_MAIN) $(OBJS_DIR) $(LIBFT)
	@echo "$(YELLOW)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS_MAIN) $(OBJS_DIR) $(LIBFT) -o $(NAME)

$(OBJS_MAIN): $(MAIN_SRC) | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE_FLAGS) -lreadline

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_FLAGS)

$(LIBFT):
	@make -C ./libft -s

clean:
	@echo "$(RED)Removing objects$(RESET)"
	@rm -rf $(OBJS_DIR)
	@make clean -C ./libft -s

fclean: clean
	@echo "$(RED)Removing $(NAME)$(RESET)"
	@rm -rf $(NAME)
	@echo "$(RED)Removing Libft$(RESET)"
	@rm -rf $(LIBFT)

re:	fclean all
	@echo "$(ORANGE)Re-Done!!$(RESET)"

.PHONY: all clean fclean re
