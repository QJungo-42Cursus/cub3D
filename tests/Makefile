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
else
GTEST =		./libgtest.a
LEAKS =		leaks --atExit --
endif

san:
	@make -C ../libft
	$(CC) $(CFLAGS) $(SAN) $(SRCS) $(GTEST) $(LIBFT_A) -o $(NAME)

$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(SAN) $(OBJS) $(GTEST) $(LIBFT_A) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run_tests:
	#@echo "Running tests with leaks"
	#make all
	#$(RM) all_.o
	#$(LEAKS) ./$(NAME) || true
	#
	@echo "Running tests with sanitizers"
	make san
	$(RM) all_.o
	./$(NAME)
	$(RM) $(NAME).dSYM
