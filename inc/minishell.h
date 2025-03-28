/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 20:35:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "built_in.h"
# include "lexing.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 1024

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
	int		append;
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
	char	*content;
	int		type;
	int		pipe[2];
	void	*next;
}	t_pipe;

typedef	struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
} t_env;

typedef struct s_shelldata
{
	char	*input;
	int		on_word;
	int		count;
	char	**token_arr;
	t_cmd	*tokens;
	t_env	*env;
}	t_shelldata;

char	*char_to_str(char c);
int		is_in_str(const char *str, char c);
int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

void	execute_command(t_shelldata *shell);

#endif
