CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = pipex
RM = rm -rf

SRCS_FOLDER = srcs/
BONUS_SRCS_FOLDER = srcs_bonus/
LIBS_FOLDER = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER = objects/

SRCS = $(SRCS_FOLDER)parsing/parsing_utils.c \
	$(SRCS_FOLDER)parsing/parsing.c \
	$(SRCS_FOLDER)pipex_struct/cmd_lst.c \
	$(SRCS_FOLDER)pipex_struct/pipex_struct.c \
	$(SRCS_FOLDER)pipex.c \

BONUS_SRCS = $(BONUS_SRCS_FOLDER)parsing/parsing_utils.c \
	$(BONUS_SRCS_FOLDER)parsing/parsing.c \
	$(BONUS_SRCS_FOLDER)pipex_struct/cmd_lst.c \
	$(BONUS_SRCS_FOLDER)pipex_struct/pipex_struct.c \
	$(BONUS_SRCS_FOLDER)pipex.c \

LIBS_SRCS = $(LIBS_FOLDER)libft/ft_bzero.c \
	$(LIBS_FOLDER)libft/ft_calloc.c \
	$(LIBS_FOLDER)libft/ft_memcpy.c \
	$(LIBS_FOLDER)libft/ft_putchar_fd.c \
	$(LIBS_FOLDER)libft/ft_putstr_fd.c \
	$(LIBS_FOLDER)libft/ft_split.c \
	$(LIBS_FOLDER)libft/ft_strchr.c \
	$(LIBS_FOLDER)libft/ft_strdup.c \
	$(LIBS_FOLDER)libft/ft_strjoin.c \
	$(LIBS_FOLDER)libft/ft_strlen.c \
	$(LIBS_FOLDER)libft/ft_strncmp.c \
	$(LIBS_FOLDER)libft/ft_substr.c \
	$(LIBS_FOLDER)ft_printf/ft_printf.c \
	$(LIBS_FOLDER)ft_printf/lltoa.c \
	$(LIBS_FOLDER)ft_printf/printing_utils.c \
	$(LIBS_FOLDER)ft_printf/ulltoa.c \
	$(LIBS_FOLDER)ft_printf/xtoa.c \

SRCS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(SRCS:.c=.o))
LIBS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(LIBS_SRCS:.c=.o))
BONUS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(BONUS_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(SRCS_OBJS) $(LIBS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

bonus: $(BONUS_OBJS) $(LIBS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS_FOLDER)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I $(INCLUDES_FOLDER) -c $< -o $@

clean:
	$(RM) $(OBJECTS_FOLDER)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
