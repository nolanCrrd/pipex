CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = push_swap
RM = rm -rf

SRCS_FOLDER = srcs/
LIBS_FOLDER = libs/
INCLUDES_FOLDER = includes/
OBJECTS_FOLDER = objects/

SRCS = \
	

LIBS_SRCS = \


SRCS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(SRCS:.c=.o))
LIBS_OBJS = $(addprefix $(OBJECTS_FOLDER),$(LIBS_SRCS:.c=.o))

all: $(NAME)

$(NAME): $(SRCS_OBJS) $(LIBS_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJECTS_FOLDER)%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDES_FOLDER) -c $< -o $@

clean:
	$(RM) $(OBJECTS_FOLDER)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
