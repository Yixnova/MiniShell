# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 10:42:59 by busseven          #+#    #+#              #
#    Updated: 2025/03/26 13:12:41 by yigsahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_shell
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS =	main.c\
		input_utils.c\
		signals.c\
		execute.c\
		./built_in/env_cmd.c\
		./built_in/echo_cmd.c\
		./built_in/cd_cmd.c\
		./built_in/env_utils.c\
		./built_in/set_cmd.c\
		./built_in/export_cmd.c\
		./built_in/exit_cmd.c\

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)
	@echo "Building all..."

$(NAME): $(OBJS) $(LIBFT)
	@echo "Creating executable..."
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) -L/opt/homebrew/opt/readline/lib -lreadline
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
