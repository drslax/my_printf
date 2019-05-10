# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mherrat <mherrat@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/14 22:01:30 by mherrat           #+#    #+#              #
#    Updated: 2019/04/21 00:38:50 by mherrat          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
NAME	= libftprintf.a
SRC		= ./src/flags.c ./src/numbers.c ./src/numbers2.c ./src/ft_printf.c ./src/strings.c ./src/float.c ./src/libft/*.c
SRCS	= *.o

all: $(NAME)

$(NAME): 

	$(CC) -c $(FLAGS) $(SRC)
	ar rc $(NAME) $(SRCS)
	ranlib $(NAME)
%.o: %.c
	$(CC) $< $(FLAGS) -c -o $@

clean:
	rm -f ./*.o $(SRCS)

fclean: clean

	rm -f $(NAME)

re: fclean all
