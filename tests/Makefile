NAME =		test
CC =		c++
CFLAGS =	-Wall -Wextra -Werror
RM =		rm -f
SRCS =		main.cpp
OBJS =		$(SRCS:.cpp=.o)
GTEST =		./libgtest.a
LIBFT_A = ../libft/libft.a


all: $(OBJS)
	@make -C ../libft
	$(CC) $(CFLAGS) $(GTEST_INC) $(OBJS) $(GTEST) $(LIBFT_A) -o $(NAME)
	./$(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
