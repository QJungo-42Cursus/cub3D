
SRCS_TEST =		main.cpp
OBJS_TEST =		$(SRCS_TEST:.cpp=.o)

GTEST =			./libgtest.a
#GTEST =			/usr/local/lib/libgtest.a

ifeq ($(shell uname), Darwin)
GTEST_INC = -std=c++17 -I/Users/qjungo/.brew/include
GTEST =		/Users/qjungo/.brew/lib/libgtest.a
endif

NAME_TEST = test
LIBFT_A = ../libft/libft.a

all:
	@make -C ../libft
	c++ $(GTEST_INC) $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)
