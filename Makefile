NAME =		miniRT
SRCS =		srcs/gnl/get_next_line_utils.c \
			srcs/gnl/get_next_line.c \
			srcs/hit_objects/hit_plane.c \
			srcs/hit_objects/hit_triangle.c \
			srcs/hit_objects/hit_sphere.c \
			srcs/hit_objects/hit_square.c \
			srcs/hit_objects/hit_cylinder.c \
			srcs/hit_objects/intersection.c \
			srcs/hit_objects/hit_disk.c \
			srcs/math/matrix.c \
			srcs/math/ray_basis.c \
			srcs/math/rotation.c \
			srcs/math/transform_1.c \
			srcs/math/transform_2.c \
			srcs/math/vector_utils.c \
			srcs/math/vectors.c \
			srcs/parser/atoi_atof.c \
			srcs/parser/parse_scene_elems.c \
			srcs/parser/parse_objs.c \
			srcs/parser/parser.c \
			srcs/parser/parsing_utils.c \
			srcs/utils/add_scene.c \
			srcs/utils/error.c \
			srcs/utils/utils.c \
			srcs/utils/free.c \
			srcs/utils/prints.c \
			srcs/utils/prints_2.c \
			srcs/bmp.c \
			srcs/lights.c \
			srcs/ray_tracer.c \
			main.c

OBJS =		${SRCS:.c=.o}
MLX_FLAGS =	-fsanitize=address -Lminilibx -framework OpenGL -framework AppKit -lminilibx 
FLAGS =		-g -Wall -Wextra -Werror
RM =		rm -rf
CC =		gcc

all:		$(NAME)

%.o: %.c
			$(CC) $(FLAGS) -O3 -msse3 -I ./includes/ -I ./mlx/ -c $< -o $@

$(NAME):	${OBJS} #mlxmake
			$(CC) -g $(OBJS) -Lmlx -lmlx -framework OpenGL -framework AppKit -O3 -msse3 -o $(NAME)

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
			./miniRT samples/sample.rt
bonus:		all
mlxmake:
	make -C mlx/ all
	mv mlx/libmlx.a .
	make -C mlx/ clean
.PHONY: all clean fclean re run
.SILENT: