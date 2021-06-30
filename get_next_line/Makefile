# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/30 12:41:07 by kgulati           #+#    #+#              #
#    Updated: 2021/06/30 12:43:24 by kgulati          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
INCLUDES = get_next_line.h
FILES = get_next_line.c \
		get_next_line_utils.c

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	gcc -Wall -Werror -Wextra -c $(FILES)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
