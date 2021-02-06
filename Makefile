NAME = miniRT
CC = gcc
FLAGS = -lmlx -framework OpenGL -framework AppKit
SRDIR = ./srcs
SRCS = $(SRDIR)/*.c
OBJS = $(SRC:.c=.o)

$(NAME):	$(OBJS)
		$(CC) $(FLAGS) $(SRCS) main.c -o $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY: all clean fclean re bonus