# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyildiz <gyildiz@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/01 13:58:08 by gyildiz           #+#    #+#              #
#    Updated: 2025/03/02 13:03:52 by gyildiz          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =			so_long_main.c error_handling.c utils.c
				
OBJS =			$(SRCS:.c=.o)

EXE_NAME =		so_long

LIBFT =			./Libft/libft.a

CC =			gcc
CFLAGS =		-g

all:			$(LIBFT) $(EXE_NAME)

$(EXE_NAME):	$(OBJS) $(LIBFT)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(EXE_NAME)

$(LIBFT):
				make -C ./Libft all

fclean: clean
				rm -rf $(EXE_NAME)
				make -C ./Libft fclean

clean: 
				rm -rf $(OBJS)
				make -C ./Libft clean

re: fclean all

.PHONY: all fclean clean re