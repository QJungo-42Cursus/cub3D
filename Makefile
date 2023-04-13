NAME =		cube3D
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror -O2
RM =		rm -f
LIBFT =		-L./libft -lft
SRCS =		\
			src/main.c \
			src/utils.c \
			src/init.c \
			src/parsing/parsing.c \
			src/parsing/get_info_by_id.c \
			src/parsing/set_textures_path.c \
			src/parsing/set_tiles.c \
			src/parsing/check_tiles.c \
			src/parsing/check_tiles_after.c \
			src/parsing/set_colors.c \
			src/parsing/get_all_file.c \
			src/run/run.c \
			src/run/hooks.c \
			src/run/draw_minimap.c \
			src/run/move_toward.c \
			src/raycasting/player_action.c \
			src/raycasting/draw_column.c \
			src/raycasting/get_impact_point.c \
			src/raycasting/init_and_set_ray.c \
			src/raycasting/ray_cast.c

OBJS =		$(SRCS:.c=.o)

## MLX ##
ifeq ($(shell uname), Linux)
MLX =		-Lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LEAKS =		valgrind -q --leak-check=full --track-origins=yes
else
MLX =		-Lmlx -lmlx -framework OpenGL -framework AppKit -lz
LEAKS =		leaks --atExit --
endif

########

all: $(NAME)

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@make clean -C ./libft
	$(RM) $(OBJS)

fclean: clean
	rm -f ../libft/libft.a
	$(RM) $(NAME)

re: fclean all

###

ulibft:
	$(RM) -r ./libft/.git
	cp -r ./libft ./
	$(RM) -r ./libft/.git
	make re

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san:
	@make -C ./libft
	$(CC) $(CFLAGS) $(SAN) $(SRCS) $(LIBFT) $(MLX) -o $(NAME) 

leaks: all
	$(LEAKS) ./$(NAME) maps/basic.cub

t:
	make san
	./$(NAME) maps/basic.cub

.PHONY: all clean fclean re
