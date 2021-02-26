NAME =		miniRT
SRCS =		srcs/gnl/get_next_line_utils.c \
			srcs/gnl/get_next_line.c \
			srcs/hit_objects/hit_plane.c \
			srcs/hit_objects/hit_sphere.c \
			srcs/hit_objects/hit_square.c \
			srcs/math/matrix.c \
			srcs/math/ray_basis.c \
			srcs/math/tranform_1.c \
			srcs/math/tranform_2.c \
			srcs/math/vector_utils.c \
			srcs/math/vectors.c \
			srcs/parser/atoi_atof.c \
			srcs/parser/parse_c_r_l.c \
			srcs/parser/parser.c \
			srcs/parser/parsing_utils.c \
			srcs/utils/error.c \
			srcs/utils/free.c \
			srcs/utils/prints.c \
			srcs/add_scene.c \
			srcs/camera.c \
			srcs/color.c \
			srcs/intersection.c \
			srcs/lights.c \
			srcs/ray_tracer.c \
			srcs/scene.c \
			main.c

OBJS =		${SRCS:.c=.o}
MLX_FLAGS =	-Lminilibx -framework OpenGL -framework AppKit -lminilibx
FLAGS =		-g -Wall -Wextra -Werror
RM =		rm -rf
CC =		gcc

all:		$(NAME)

%.o: %.c
			$(CC) $(FLAGS) -I ./includes/ -I ./mlx/ -c $< -o $@

$(NAME):	${OBJS}
			$(CC) -g $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:		
			$(RM) $(OBJS)
fclean:		clean
			$(RM) $(NAME)
re:			fclean all
norm:
			rm norm.txt
			norminette srcs/*/*.c  includes/*.h > norm.txt
run:		
			make
			./miniRT samples/square.rt
.PHONY: all clean fclean re