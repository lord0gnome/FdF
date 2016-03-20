# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guiricha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 16:55:06 by guiricha          #+#    #+#              #
#    Updated: 2016/03/20 18:26:48 by guiricha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c parse.c
NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
OBJ_NAME = $(SRC_NAME:.c=.o)
FRAMEWORKS = -framework OpenGL -framework AppKit
STCS = libmlx.a libftprintf.a libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ_NAME)
	rm -f libft.a
	@echo "Making";
	@echo "    __    ________  ____________";
	@echo "   / /   /  _/ __ )/ ____/_  __/";
	@echo "  / /    / // __  / /_    / /   ";
	@echo " / /____/ // /_/ / __/   / /    ";
	@echo "/_____/___/_____/_/     /_/     ";
	make re -C libft && cp -f libft/libft.a ./
	@echo "                                \n\nMaking";
	@echo " .----------------.  .----------------.  .----------------. ";
	@echo "| .--------------. || .--------------. || .--------------. |";
	@echo "| |  _________   | || |  ________    | || |  _________   | |";
	@echo "| | |_   ___  |  | || | |_   ___ \`.  | || | |_   ___  |  | |";
	@echo "| |   | |_  \_|  | || |   | |   \`. \ | || |   | |_  \_|  | |";
	@echo "| |   |  _|      | || |   | |    | | | || |   |  _|      | |";
	@echo "| |  _| |_       | || |  _| |___.' / | || |  _| |_       | |";
	@echo "| | |_____|      | || | |________.'  | || | |_____|      | |";
	@echo "| |              | || |              | || |              | |";
	@echo "| '--------------' || '--------------' || '--------------' |";
	@echo " '----------------'  '----------------'  '----------------' ";
	$(CC) -o fdf $(OBJ_NAME) GNL/get_next_line.c $(STCS) $(FRAMEWORKS)
$(OBJ_NAME):
	$(CC) $(CFLAGS) -c $(SRC_NAME)
clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
