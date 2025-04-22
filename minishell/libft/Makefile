RED=\033[1;31m
YELLOW = \033[1;33m
ORANGE = \033[1;38;5;214m
GREEN = \033[1;32m
CYAN = \033[1;36m
RESET = \033[0m

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJDIR = build
INCLUDES = include/
INCLUDES_FLAGS = -I$(INCLUDES)

SRC = src
MAIN = main

# Dirs
DIR_CHECK = ft_check
DIR_FD = ft_fds
DIR_LISTS = ft_list
DIR_MEM = ft_memory
DIR_NUM = ft_num
DIR_STR = ft_strings
DIR_PRINTF = ft_printf
DIR_GNL = gnl

SRC_CHECK =	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_toupper.c \
			ft_tolower.c ft_isspace.c

SRC_FD =	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c

SRC_LISTS =	ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c ft_lstdelone_bonus.c \
			ft_lstlast_bonus.c ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c

SRC_MEM =	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_calloc.c ft_memmove.c ft_memset.c ft_bzero.c

SRC_NUM =	ft_atoi.c ft_atoi_base.c ft_strtol.c

SRC_STR =	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c \
			ft_strcmp.c ft_count_words.c ft_getenv.c

PRINTF =	ft_putchar.c ft_putstr.c ft_printnbr.c ft_itoh.c ft_printunbr.c ft_printptr.c \
			ft_printf.c

SRC_GNL =	get_next_line.c get_next_line_utils.c

SRCS_DIR =	$(addprefix $(SRC)/, $(addprefix $(DIR_PRINTF)/, $(PRINTF))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_GNL)/, $(SRC_GNL))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_STR)/, $(SRC_STR))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_CHECK)/, $(SRC_CHECK))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_LISTS)/, $(SRC_LISTS))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_MEM)/, $(SRC_MEM))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_NUM)/, $(SRC_NUM))) \
			$(addprefix $(SRC)/, $(addprefix $(DIR_FD)/, $(SRC_FD))) \

OBJS_DIR = $(addprefix $(OBJDIR)/, $(SRCS_DIR:$(SRC)/%.c=%.o))

all: $(NAME)

$(NAME): $(OBJS_DIR)
	@echo "$(YELLOW)Building Libft$(RESET)"
	@ar rcs $(NAME) $(OBJS_DIR)
	@echo "$(GREEN)Done!$(RESET)"


$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES_FLAGS)


clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re