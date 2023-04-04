NAME =		cube3D
CC =		gcc
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -f
LIBFT =		-L./../libft -lft
SRCS =		\
			main.c \
			utils.c \
			parsing/parsing.c \
			parsing/get_info_by_id.c \
			parsing/set_textures_path.c \
			parsing/set_tiles.c \
			parsing/check_tiles.c \
			parsing/check_tiles_after.c \
			parsing/set_colors.c \
			parsing/get_all_file.c \
			fillscreen/fillscreen.c \

OBJS =		$(SRCS:.c=.o)

## MLX ##
ifeq ($(shell uname), Linux)
MLX =		-L./../mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
LEAKS =		valgrind -q --leak-check=full --track-origins=yes
else
MLX =		-L./../mlx -lmlx -framework OpenGL -framework AppKit -lz
LEAKS =		leaks --atExit --
endif

########

all: $(NAME)

$(NAME): $(OBJS)
	make -C ../libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) -o $(NAME)

clean:
	@make clean -C ../libft
	@make clean -C ../tests
	$(RM) $(OBJS)

fclean: clean
	@make fclean -C ../tests
	rm -f ../libft/libft.a
	$(RM) $(NAME)

re: fclean all

###

ulibft:
	$(RM) -r ../libft/.git
	cp -r ../../libft ../
	$(RM) -r ../libft/.git
	make re

run_tests: all
	make run_tests -C ../tests

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san:
	@make -C ../libft
	$(CC) $(CFLAGS) $(SAN) $(SRCS) $(LIBFT) $(MLX) -o $(NAME) 

leaks: all
	$(LEAKS) ./$(NAME) tests/test_files/basic.cub

.PHONY: all clean fclean re
