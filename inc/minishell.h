/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 18:31:23 by busseven         ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "built_in.h"
# include "lexing.h"
# include "expand.h"
# include "free_functions.h"
# include "execute.h"
# include "utils.h"
# include "errors.h"
# include "parse.h"
# include "errno.h"
# include "termios.h"
# include <sys/stat.h>

# define BUFFER_SIZE 1024

extern int	g_signal_flag;

// types 0 = pipe, 1 = here_doc, 2 = input, 3 = output

typedef struct s_cmd
{
	char			**tokens;
	char			**args;
	int				arg_count;
	char			**redirs;
	char			**limiter_arr;
	int				**hd_arr;
	int				*hd_parsedollar;
	int				hd_index;
	int				input;
	int				index;
	int				output;
	int				append;
	int				input_type; //stdin, pipe or file or heredoc
	int				output_type; //stdout pipe or file
	int				fd_count;
	int				hd_count;
	int				redir_count;
	int				has_hd;
	int				*file_descs;
	int				parse_error;
	int				invalid; // Komut gerçekten bulunuyor mu? Yoksa error ve exit;
	int				built_in; // Komut built-in ise 1, değilse 0
	char			*path; // Bulunan yürütülebilir dosyanın tam yolu
	char			*faulty_token;
	int				exit_code;
	char			*err_msg;
	int				err_type;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	char			**envp;
}	t_env;

typedef struct s_shelldata
{
	char		*input;
	int			on_word;
	int			cmd_count;
	int			count;
	char		**tokens;
	char		**paths;
	t_cmd		**cmds;
	int			**pipes;
	t_env		*env;
	int			*pids;
	int		command_index;
	int		exit_status;
	char	**input_arr;
	char	*read_line;
}	t_shelldata;

void	handle_input_and_history(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);
char	*get_next_line(int fd, int i);
void	set_envp(t_shelldata *shell, t_env *env);
void 	setup_child_signals(void);
void 	setup_process_signals(void);

#endif
