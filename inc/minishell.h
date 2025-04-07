/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/04/07 18:34:08 by busseven         ###   ########.fr       */
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
# include "expand.h"

# define BUFFER_SIZE 1024

//types 0 = pipe, 1 = here_doc, 2 = input, 3 = output
typedef	struct	s_output
{
	int		type;
	int		append;
	int		fd;
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
	int		arg_count;
	char	**args;
	int		input;
	int		output;
	int		redir;
	void	*next;
}	t_cmd;

typedef	struct	s_heredoc
{
	int		type;
	int		doc[2];
	char	*limiter;
	void	*next;
}	t_heredoc;

typedef	struct	s_pipe
{
	int		type;
	int		pipe[2];
	void	*next;
}	t_pipe;

typedef	struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shelldata
{
	char	*input;
	int		on_word;
	int		count;
	char	**token_arr;
	char	**paths;
	t_cmd	**tokens;
	t_env	*env;
	int		exit_status;
}	t_shelldata;

extern t_shelldata *g_shell;

char	*char_to_str(char c);
int		is_in_str(const char *str, char c);
int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);
int		*ft_intjoin(int	*arr, int n);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

void	execute_command(t_shelldata *shell);

#endif
