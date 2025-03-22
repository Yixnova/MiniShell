# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 10:42:59 by busseven          #+#    #+#              #
#    Updated: 2025/03/22 19:25:07 by yigsahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c input_utils.c
OBJ = $(SRC:.c=.o)
NAME = minishell
NAME = mini_shell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c\
		input_utils.c\
		signals.c\

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)
	@echo "Building all..."

$(NAME): $(OBJS) $(LIBFT)
	@echo "Creating executable..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
$(LIBFT):
	@echo "Building libft..."
	@make -C libft

clean:
	@echo "Cleaning object files..."
	@rm -f $(OBJS)
	@make -C libft clean

fclean: clean
	@echo "Removing executable and cleaning..."
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
	@echo "Rebuilding all..."

.PHONY: all clean fclean re
