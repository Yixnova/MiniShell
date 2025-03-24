/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/24 10:08:26 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>

typedef	struct	s_output
{
	int		type;
	int		append;
	char	*path;
	void	*next;
}	t_output;

typedef	struct	s_input
{
	int		type;
	int		fd;
	char	*path;
	void	*next;
}	t_input;

typedef	struct	s_cmd
{
	int		type;
	char	**args;
	int		input;
	int		output;
	void	*next;
}	t_cmd;

typedef	struct	s_heredoc
{
	int		type;
	int		pipe[2];
	char	*limiter;
	void	*next;
}	t_heredoc;

typedef	struct	s_pipe
{
	int		type;
	int		pipe[2];
	void	*next;
}	t_pipe;

typedef struct s_shelldata
{
	char	*input;
	int		on_word;
	int		count;
	char	**token_arr;
	t_cmd	*tokens;
}	t_shelldata;

int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);
void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);
void	tokenize_input(t_shelldata	*data);
void	unclosed_quotes();
char	**split_into_words(char *str);

#endif
