# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyildiz <gyildiz@student.42istanbul.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 13:58:08 by gyildiz           #+#    #+#              #
#    Updated: 2025/03/14 00:38:21 by gyildiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			so_long_main.c free_functions.c error_main.c utils.c\
				error_map_chars.c error_map_shape.c debug_functions.c\
				game_screen.c
				
				
OBJS =			$(SRCS:.c=.o)

EXE_NAME =		so_long

LIBFT =			./Libft/libft.a

MINXLIB =	./minilibx-linux/libmlx.a

CC =			gcc
CFLAGS =		-g
MLXFLAGS =		-Lminilibx-linux
X =				-lmlx -lX11 -lXext

all:			$(LIBFT) $(EXE_NAME)

$(EXE_NAME):	$(OBJS) $(LIBFT) $(MINXLIB)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(EXE_NAME) $(MLXFLAGS) $(X)

$(LIBFT):
				make -C ./Libft all

$(MINXLIB):
				make -C ./minilibx-linux all

fclean: clean
				rm -rf $(EXE_NAME)
				make -C ./Libft fclean

clean: 
				rm -rf $(OBJS)
				make -C ./Libft clean

re: fclean all

.PHONY: all fclean clean re