NAME = philo

SRCS = main.c utils.c utils2.c utils3.c

FLAGS = -Werror -Wextra -Wall

$(NAME) :
	gcc $(FLAGS) $(SRCS) -o $(NAME)
	
all: $(NAME)

clean: 
	rm -rf *.dSYM

fclean: clean
	rm -rf $(NAME)

re: fclean all
