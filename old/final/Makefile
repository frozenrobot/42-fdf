# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kgulati <kgulati@student.42wolfsburg.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 23:35:06 by kgulati           #+#    #+#              #
#    Updated: 2021/07/22 00:11:39 by kgulati          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf.a
FILES = atoi.c \
		general.c \
		grid.c \
		draw_points.c \
		hex.c \
		split.c \
		main_sub.c \
		get_next_line.c \
		defines.c \
		get_next_line_utils.c 

OBJ = $(FILES:.c=.o)

all: $(NAME)

$(NAME):
	gcc -c -Wall -Werror -Wextra $(FILES)
	ar rcs $(NAME) $(OBJ)
	gcc main.c -Wall -Werror -Wextra minilibx/libmlx_x86_64.a -L/usr/include/X11/extensions -lX11 -lXext fdf.a -o fdf

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME) fdf

re: fclean all
