NAME =		tests
CC =		c++
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -f
GTEST =		./libgtest.a
LIBFT_A = ../libft/libft.a

SRCS =		main.cpp all_.cpp \
			testParsing.cpp \
			testMain.cpp \

OBJS =		$(SRCS:.cpp=.o)


$(NAME): $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(OBJS) $(GTEST) $(LIBFT_A) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run_tests: all
	./$(NAME)
