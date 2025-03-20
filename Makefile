# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busseven <busseven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 10:42:59 by busseven          #+#    #+#              #
#    Updated: 2025/03/20 09:31:16 by busseven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c input_utils.c
OBJ = $(SRC:.c=.o)
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFTPRINTF	= ./ft_printf/libftprintf.a
LIBS = $(LIBFTPRINTF)

all: $(LIBFTPRINTF) $(NAME)

$(NAME): $(OBJ) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $(NAME) $(LIBS)

$(LIBFTPRINTF):
	$(MAKE) -C ./ft_printf all

fclean: clean
	make -C ft_printf fclean
	rm -rf $(NAME)

clean:
	rm -f $(OBJ)
	make -C ./ft_printf clean

re: fclean all

.PHONY: all clean fclean re