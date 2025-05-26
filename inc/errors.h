/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:50:41 by busseven          #+#    #+#             */
/*   Updated: 2025/05/26 13:28:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "minishell.h"

typedef struct s_cmd		t_cmd;
typedef struct s_shelldata	t_shelldata;

int		open_error(t_cmd *cmd, char *file, int redir_num);
void	execve_error(char *cmd);
int		command_not_found(t_cmd *tcmd, char *cmd);
int		directory_error(t_cmd *cmd, char *dir);
int		no_such_file(t_cmd *cmd, char *file);
void	syntax_error_eof(void);
char	*check_token_errors(char **tokens);
int		syntax_error_invalid_token(char *token, t_shelldata *data);
int		quote_error(t_shelldata *data);
void	heredoc_eof(t_cmd *cmd, int line_num, int h, char *line);
void	single_dot_error(void);
int		is_all_dots(char *str);

#endif
