NAME = philo

LIBFT_PATH = ./libft

SRCS = *.c
FLAGS = -Werror -Wextra -Wall

ASAN =  -g -fsanitize=address
$(NAME) :
	make -C $(LIBFT_PATH)
	gcc $(ASAN) $(SRCS) ./libft/libft.a  -o $(NAME)
	
all: $(NAME)

clean: 
	make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME) *.dSYM
	make fclean -C $(LIBFT_PATH)

re: fclean all  
	 

#re: fclean all