# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rteles-f <rteles-f@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 13:50:32 by rteles-f          #+#    #+#              #
#    Updated: 2023/11/10 22:16:24 by rteles-f         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

COLOR_RESET =	\033[0m
COLOR_GREEN =	\033[32m

NAME			= 	cub3d

CC				= 	cc -pthread -g -fsanitize=address#-fsanitize=thread# 

CFLAGS			= 	-Iheaders/ #-Wall -Wextra -Werror 

MLX_LIB_DIR     =	./mlx_linux

MLX_INCLUDE     =	-Imlx_linux

MLX_FLAGS		=	-L$(MLX_LIB_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

RM				= 	rm -f

INCLUDES		= 	-Iheaders/

# SRCS			=	src/*/*.c
SRCS			=	$(shell find src/ -name '*.c')

OBJS			= 	$(SRCS:.c=.o)

all: 		$(NAME)

$(NAME):	$(OBJS)
			@$(MAKE) -s -C mlx_linux
			@$(CC) $(^) $(MLX_FLAGS) -o $(@)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Compiled"

%.o: %.c
			@$(CC) -c $(^) $(CFLAGS) $(MLX_INCLUDE) -o $(@)

clean:
			@$(RM) $(OBJS)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Clean"

fclean: 	clean
			@$(RM) $(NAME)
			@echo "[$(COLOR_GREEN)info$(COLOR_RESET)]: Full"

re:			fclean all

norm :
			@norminette -R CheckForbiddenSourceHeader $(SRCS) headers/

r:
			@make re && make clean && clear && ./$(NAME)

v:
			make re && clear && valgrind -s --leak-check=full --show-leak-kinds=all ./cub3d maps/second.cub


.PHONY: 	all re clean fclean