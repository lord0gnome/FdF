# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guiricha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 16:55:06 by guiricha          #+#    #+#              #
#    Updated: 2016/03/17 14:30:03 by guiricha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c parse.c point_lists.c
NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
OBJ_NAME = $(SRC_NAME:.c=.o)
FRAMEWORKS = -framework OpenGL -framework AppKit
STCS = libft.a libmlx.a libftprintf.a
all: $(NAME)
	
$(NAME): $(OBJ_NAME)
	$(CC) $(CFLAGS) -o fdf $(OBJ_NAME) $(STCS) GNL/get_next_line.c $(FRAMEWORKS) 
$(OBJ_NAME):
	@$(CC) $(CFLAGS) -c $(SRC_NAME)
clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
