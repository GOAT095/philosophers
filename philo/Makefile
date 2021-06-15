NAME = philo


SRCS = main.c

FLAGS = -Werror -Wextra -Wall

ASAN =  -g -fsanitize=address
$(NAME) :
	gcc $(ASAN) $(SRCS) -o $(NAME)
	
all: $(NAME)

clean: 
	rm -rf *.dSYM

fclean:
	rm -rf $(NAME)

re: fclean all  
	 

#re: fclean all