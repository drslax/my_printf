FLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRC = *.c

all: $(NAME)

$(NAME):
	gcc -c $(FLAGS) $(SRC)
	ar rc $(NAME) *.o
	ranlib $(NAME)
clean:
	rm -f *.o libft/*.o
fclean: clean
	rm -f $(NAME)
	rm -f *.o libft/*.o
re: fclean all
