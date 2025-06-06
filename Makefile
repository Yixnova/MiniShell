# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/19 10:42:59 by busseven          #+#    #+#              #
#    Updated: 2025/06/05 19:13:13 by yigsahin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lreadline
MACOS = -L/opt/homebrew/opt/readline/lib

SRCS =	main.c\
		./utils/input_utils.c\
		./signals/signals.c\
		./execute/execute.c\
		./execute/handle_cmd.c\
		./built_in/env_cmd.c\
		./built_in/echo_cmd.c\
		./built_in/cd_cmd.c\
		./built_in/env_utils.c\
		./built_in/set_cmd.c\
		./built_in/export_cmd.c\
		./built_in/export_utils.c\
		./built_in/exit_cmd.c\
		./built_in/sort_and_print.c\
		./lexer/lexer.c\
		./lexer/lexer_errors.c\
		./lexer/lexer_array.c\
		./lexer/lexer_utils.c\
		./lexer/remove_quotes.c\
		./expander/expand.c\
		./expander/expand_utils.c\
		./expander/expand_utils2.c\
		./parser/cmd_list.c \
		./parser/make_arg_array.c \
		./parser/make_redir_arr.c \
		./parser/parse_errors.c \
		./parser/make_limiter_array.c \
		./parser/get_next_line.c \
		./parser/parser_utils.c \
		./parser/here_doc.c \
		./execute/processes.c \
		./execute/processes_utils.c \
		./execute/process_error.c\
		./execute/find_command_path.c\
		./parser/init_parsedata.c \
		./execute/redir_utils.c \
		./execute/check_utils.c \
		./execute/envp_utils.c \
		./utils/input_utils2.c\
		./utils/free_utils.c\
		./lexer/handle_pipe.c\
		./lexer/edit_input.c\
		./lexer/input_arr.c\
		./signals/child_signals.c\
		./signals/here_doc_signals.c\
		./lexer/ft_strtrim_free.c\
		./execute/process_error2.c\

OBJS = $(SRCS:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)
	@echo "Building all..."

$(NAME): $(OBJS) $(LIBFT)
	@echo "Creating executable..."
	@$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME) $(LIBS) $(MACOS)
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

clear:
	clear
	@echo "Everything is okay. LFG! :) -> ./minishell"

comp: all clean clear

.PHONY: all clean fclean re comp
