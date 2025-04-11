/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 11:45:44 by busseven         ###   ########.fr       */
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
# include <sys/wait.h>

# define BUFFER_SIZE 1024

extern int	g_signal_flag;

// types 0 = pipe, 1 = here_doc, 2 = input, 3 = output

typedef struct s_cmd
{
	char	**tokens;
	char	**args;
	char	**redirs;
	char	**limiter_arr;
	int		pipe[2];
	int		**hd_arr;
	int		input;
	int		output;
	int		hd_index;
	int		redir_index;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;


typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shelldata
{
	char		*input;
	int			on_word;
	int			count;
	char		**token_arr;
	char		**paths;
	t_cmd		**cmds;
	t_env		*env;
	int		exit_status;
}	t_shelldata;

char	*char_to_str(char c);
int		is_in_str(const char *str, char c);
int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);
int		*ft_intjoin(int *arr, int n);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

void	execute_command(t_shelldata *shell);
void	parser(t_shelldata *shell, t_cmd *cmds, int i, int n);
int		is_pipe(char *str);
int		is_redir(char	*str);
void	make_arg_array(t_cmd *cmd);
void	make_redir_array(t_cmd *cmd);

#endif
