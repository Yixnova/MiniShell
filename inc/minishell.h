/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:25 by yigsahin         ###   ########.fr       */
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
# include <errno.h>
# include "../libft/libft.h"
# include "built_in.h"
# include "lexing.h"
# include "expand.h"
# include "free_functions.h"
# include "execute.h"
# include "utils.h"
# include "errors.h"
# include "parse.h"

# define BUFFER_SIZE 1024

extern int	g_signal_flag;

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
	int				input_type;
	int				output_type;
	int				fd_count;
	int				hd_count;
	int				redir_count;
	int				has_hd;
	int				*file_descs;
	int				parse_error;
	int				invalid;
	int				built_in;
	char			*path;
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
	int			command_index;
	int			exit_status;
	char		**input_arr;
	char		*read_line;
	int			iteration_count;
	char		**envp;
}	t_shelldata;

typedef struct s_lineparse
{
	int	on_word;
	int	type;
	int	in_quotes;
	int	start;
	int	count;
	int	i;
}	t_lineparse;

void	handle_input_and_history(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);
char	*get_next_line(int fd, int i);
void	set_envp(t_shelldata *shell, t_env *env, int fr);
void	setup_heredoc_signals(void);
void	setup_process_signals(void);
void	setup_tokens_signals(void);
char	*ft_threejoin_free(char *s1, const char *s2, const char *s3);
char	*ft_strtrim_free(char *s1, const char *set);
int		ends_with_pipe(char *str, int i);

#endif
