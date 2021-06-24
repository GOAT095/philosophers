NAME = philo_bonus


SRCS = main.c utils.c utils2.c utils3.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g -fsanitize=address
$(NAME) :
	gcc $(SRCS) -o $(NAME)
	
all: $(NAME)

clean: 
	rm -rf *.dSYM

fclean: clean
	rm -rf $(NAME)

re: fclean all
