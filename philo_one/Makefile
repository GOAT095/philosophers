NAME = philo_one

LIBFT_PATH = ../libft

SRCS = *.c
FLAGS = -Werror -Wextra -Wall

ASAN =  -g -fsanitize=address
$(NAME) :
	make -C $(LIBFT_PATH)
	gcc -g $(ASAN) $(SRCS) ../libft/libft.a  -o $(NAME)
	
all: $(NAME)

clean: 
	make clean -C $(LIBFT_PATH)

fclean:
	rm -rf $(NAME)
	make fclean -C $(LIBFT_PATH)
re_libft:
	make re -C ../libft
re: re_libft fclean all
	 

#re: fclean all