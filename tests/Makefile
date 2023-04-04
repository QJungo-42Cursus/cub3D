NAME =		tests
CC =		c++
CFLAGS = -std=c++17
RM =		rm -f
LIBFT_A = ../libft/libft.a

SRCS =		\
			all_.cpp \
			testParsing.cpp \
			testMain.cpp \
			main.cpp \

OBJS =		$(SRCS:.cpp=.o)


SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment \
		-g

ifeq ($(shell uname), Linux)
GTEST =		./libgtest_Linux.a
LEAKS =		valgrind -q --leak-check=full --track-origins=yes
MLX =		-L./../mlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz
else
GTEST =		./libgtest.a
LEAKS =		leaks --atExit --
MLX =		-L./../mlx -lmlx -framework OpenGL -framework AppKit -lz
endif

san:
	$(CC) $(CFLAGS) $(SAN) $(SRCS) $(GTEST) $(LIBFT_A) $(MLX) -o $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(SAN) $(OBJS) $(GTEST) $(LIBFT_A) $(MLX) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run_tests:
	@printf "\nCompiling tests with fsanitize\n"
	@printf "==================================================================================================\n"
	make #san
	@printf "\nRunning tests with sanitizers\n"
	@printf "==================================================================================================\n"
	@$(RM) all_.o
	./$(NAME)
	@$(RM) -r $(NAME).dSYM
	@printf "\n==================================================================================================\n\n"

FS = ../src/fillscreen/fillscreen.c
img:
	gcc $(FS) image_draw/test1.c image_draw/image_draw.c $(LIBFT_A) $(MLX)
	./a.out

min: 
	gcc $(FS) image_draw/minimap.c $(LIBFT_A) $(MLX)
	./a.out
