# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: guiricha <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 16:55:06 by guiricha          #+#    #+#              #
#    Updated: 2016/04/12 14:48:33 by guiricha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME = main.c parse.c ft_atoi_hex.c ft_is_hex.c draw_pixels.c init.c \
		   get_args.c calc_z.c make_table.c keycode_func.c views.c
NAME = fdf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
OBJ_NAME = $(SRC_NAME:.c=.o)
FRAMEWORKS = -framework OpenGL -framework AppKit
STCS = libmlx.a libft.a

all: $(NAME)

$(NAME): $(LIB) $(OBJ_NAME)
	@rm -f libft.a
	@echo "Making";
	@echo "    __    ________  ____________";
	@echo "   / /   /  _/ __ )/ ____/_  __/";
	@echo "  / /    / // __  / /_    / /   ";
	@echo " / /____/ // /_/ / __/   / /    ";
	@echo "/_____/___/_____/_/     /_/     ";
	@make re -C libft && cp -f libft/libft.a ./
	@make re -C minilibx_macos && cp -f minilibx_macos/libmlx.a ./
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
	@$(CC) -o fdf $(OBJ_NAME) get_next_line.c $(STCS) $(FRAMEWORKS)
$(OBJ_NAME):
	@$(CC) $(CFLAGS) -c $(SRC_NAME)
clean:
	@rm -f *.o
	@rm -f *.a
	@make fclean -C libft
	@make clean -C minilibx_macos

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all
