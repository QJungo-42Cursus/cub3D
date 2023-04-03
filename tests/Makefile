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
	@make -C ../libft
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
	@echo "Compiling tests with fsanitize"
	@echo "============================"
	make san
	@echo "Running tests with sanitizers"
	@echo "============================"
	@$(RM) all_.o
	./$(NAME)
	#@#cd ../src && ../tests/$(NAME)
	@$(RM) -r $(NAME).dSYM
