NAME =		MiniRT
CC =		gcc
FLAGS = 	 -framework OpenGL -framework AppKit -g #-Wall -Wextra -Werror
SRCS =		srcs/add_scene.c \
			srcs/camera.c \
			srcs/color.c \
			srcs/error.c \
			srcs/intersection.c \
			srcs/lights.c \
			srcs/prints.c \
			srcs/scene.c \
			srcs/gnl/get_next_line_utils.c \
			srcs/gnl/get_next_line.c \
			srcs/math/ray_basis.c \
			srcs/math/vector_utils.c \
			srcs/math/vectors.c \
			srcs/parser/atoi_atof.c \
			srcs/parser/parse_c_r_l.c \
			srcs/parser/parser.c \
			srcs/parser/parsing_utils.c \
			main.c

OBJS =		${SRC:.c=.o}

all:		$(NAME)

.c.o:
			$(CC) $(FLAGS) -I ./includes -c $< -o ${<:.c=.o}

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -I  ./includes $(SRCS) libmlx.a -o $(NAME) -lm

clean:		
			rm -rf $(OBJS)
fclean:		clean
			rm -rf $(NAME)
re:			fclean all


			



.PHONY: all clean fclean re bonus