NAME = philo

SRCS = main.c utils.c utils2.c

FLAGS = -Werror -Wextra -Wall

SAN = -g -fsanitize=address

$(NAME) :
	gcc  $(SAN) $(SRCS) -o $(NAME)
	
all: $(NAME)

clean: 
	rm -rf *.dSYM

fclean: clean
	rm -rf $(NAME)

re: fclean all
