NAME =		cube3D
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -f
LIBFT =		-L./libft -lft
SRCS =		main.c \
			utils.c \
			parsing/parsing.c \
			parsing/get_info_by_id.c \
			parsing/set_textures_path.c \
			parsing/set_tiles.c \
			parsing/check_tiles.c \
			parsing/set_colors.c \
			parsing/get_all_file.c

OBJS =		$(SRCS:.c=.o)

## MLX ##
ifeq ($(shell uname), Linux)
MLX =		-L./minilibx-linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
MLX_REP =	minilibx-linux
MLX_RM =	rm -f minilibx-linux/libmlx_Linux.a
LEAKS =		valgrind -q --leak-check=full --track-origins=yes
else
MLX =		-L./minilibx_macos -lmlx -framework OpenGL -framework AppKit
MLX_REP =	minilibx_macos
MLX_RM =	rm -f minilibx_macos/libmlx.a
LEAKS =		leaks --atExit --
endif

########

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	make -C $(MLX_REP)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@make clean -C libft
	@make clean -C tests
	@make clean -C $(MLX_REP) 
	$(RM) $(OBJS)

fclean: clean
	$(MLX_RM)
	@make fclean -C tests
	rm -f libft/libft.a
	$(RM) $(NAME)

re: fclean all

###

test:
	make -C tests

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san:
	@make -C libft
	@make -C $(MLX_REP)
	$(CC) $(CFLAGS) $(SAN) $(SRCS) $(LIBFT) $(MLX) -o $(NAME) 

leaks: all
	$(LEAKS) ./$(NAME) a.cub

.PHONY: all clean fclean re libft test
