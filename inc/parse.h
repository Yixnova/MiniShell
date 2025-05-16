/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:47:38 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 17:49:20 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

typedef struct s_shelldata	t_shelldata;
typedef struct s_cmd		t_cmd;

int		edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n);
void	make_arg_array(t_cmd *cmd, t_shelldata *shell);
void	make_redir_array(t_cmd *cmd, t_shelldata *shell);
void	make_limiter_arr(t_cmd	*cmd);
void	make_here_documents(t_cmd *cmd);
t_cmd	*ft_cmdnew(void);
void	add_cmd(t_shelldata *shell, t_cmd *new);
void	open_all_heredoc(t_cmd *cmd);
void	init_parsedata(t_shelldata *shell);
void	make_cmd_heredocs(t_cmd *cmd, t_shelldata *shell);

#endif