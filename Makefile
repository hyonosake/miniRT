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
			srcs/utils/bmp_utils.c \
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
DOBJS =		${SRCS:.c=.d}
MLX_FLAGS =	 -Lmlx -lmlx -framework OpenGL -framework AppKit -O3 -msse3 #-fsanitize=address
FLAGS =		-g  -MMD -Wall -Wextra -Werror -O3 -msse3
RM =		rm -rf
CC =		gcc

all:		$(NAME)

%.o: %.c
			$(CC) $(FLAGS) -I ./includes/ -I ./mlx/ -c $< -o $@

$(NAME):	${OBJS} mlxmake
			$(CC) -g $(OBJS) $(MLX_FLAGS) -o $(NAME)

clean:		
			$(RM) $(OBJS)
			$(RM) $(DOBJS)
			make -C mlx/ clean
fclean:		clean
			$(RM) libmlx.dylib
			$(RM) $(NAME)
re:			fclean all
norm:		fclean
			norminette srcs  includes/*.h
run:		
			make
			./miniRT samples/sample.rt
bonus:		all
mlxmake:
	make -C mlx/ all
	cp mlx/libmlx.dylib .
	#make -C mlx/ clean
.PHONY: all clean fclean re run bonus 
.SILENT:
-include $(DOBJS)