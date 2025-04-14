# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: busseven <busseven@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 10:42:59 by busseven          #+#    #+#              #
#    Updated: 2025/04/14 16:44:03 by busseven         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mini_shell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline

SRCS =	main.c\
		./utils/input_utils.c\
		./signals/signals.c\
		./execute/execute.c\
		./built_in/env_cmd.c\
		./built_in/echo_cmd.c\
		./built_in/cd_cmd.c\
		./built_in/env_utils.c\
		./built_in/set_cmd.c\
		./built_in/export_cmd.c\
		./built_in/export_utils.c\
		./built_in/exit_cmd.c\
		./lexer/lexer.c\
		./lexer/lexer_errors.c\
		./lexer/lexer_array.c\
		./lexer/lexer_utils.c\
		./lexer/remove_quotes.c\
		./expander/expand.c\
		./expander/expand_utils.c\
		./parser/cmd_list.c \
		./parser/make_arg_array.c \
		./parser/make_redir_arr.c \
		./parser/parse_errors.c \
		./parser/make_limiter_array.c \
		./parser/get_next_line.c \
		./parser/parser_utils.c \
		./parser/here_doc.c \

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

comp: all clean

.PHONY: all clean fclean re comp
