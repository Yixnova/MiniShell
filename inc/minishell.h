/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/04/30 15:57:26 by busseven         ###   ########.fr       */
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
# include "execute.h"
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
	int				*hd_will_parsedollar;
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

int		edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n);
int		is_pipe(char *str);
int		is_redir(char	*str);
void	make_arg_array(t_cmd *cmd, t_shelldata *shell);
void	make_redir_array(t_cmd *cmd, t_shelldata *shell);
int		check_parse_errors(t_cmd *cmd);
int		free_buffer(char *buffer, int i);
char	*get_next_line(int fd, int i);
void	make_limiter_arr(t_cmd	*cmd);
int		redir_num(char	*str);
void	make_here_documents(t_cmd *cmd);
t_cmd	*ft_cmdnew(void);
void	add_cmd(t_shelldata *shell, t_cmd *new);
void	open_all_heredoc(t_cmd *cmd);
void	free_2d_char(char **arr);
void	close_pipes(t_cmd **cmds, t_shelldata *shell, int i);
void	start_processes(t_shelldata *shell, t_cmd **cmds);
void	invalid_file(char *file_name);
void	open_error(char *file, int redir_num);
char	*ft_join(char	*str, char	*joining);
void	pick_pipes(t_cmd *cmd);
void	pick_file_descriptors(t_cmd *cmd);
void	open_files(t_cmd *cmd);
int		search_in_paths(t_cmd *cmd, t_shelldata *shell);
void	init_parsedata(t_shelldata *shell);
int		check_files_and_commands(t_shelldata *data, t_cmd *cmd);
void 	open_here_document(t_cmd *cmd, int h, t_shelldata *shell);
void	make_cmd_heredocs(t_cmd *cmd, t_shelldata *shell);
int		find_command_path(t_cmd *cmd, t_shelldata *shell);
int		is_builtin_command(const char *cmd);
void	execve_error(void);
void	command_not_found(char *cmd);
void	directory_error(char *dir);
void	access_error(char *file);
int		is_directory(const char *path);
void	no_such_file(char *file);
void	access_permission_denied(char *file);
int		add_tokens(t_shelldata *data);
int		continue_quoted_input(t_shelldata *data, int type);
int		check_unclosed_quotes(t_shelldata *data);

#endif
