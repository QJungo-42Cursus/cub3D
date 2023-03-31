NAME =		cube3D
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -f
LIBFT =		-L./libft -lft
SRCS =		main.c \
			parsing/parsing.c

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
	@make clean -C $(MLX_REP) 
	$(RM) $(OBJS)

fclean: clean
	$(MLX_RM)
	rm -f libft/libft.a
	$(RM) $(NAME)

re: fclean all

###

test: $(OBJS)
	@make -C libft
	@make -C $(MLX_REP)
	$(CC) $(CFLAGS) -g $(OBJS) $(LIBFT) $(MLX) -o $(NAME)
	clear
	./fdf test_maps/42.fdf


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
