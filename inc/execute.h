/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:45:59 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/16 16:44:16 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd		t_cmd;
typedef struct s_shelldata	t_shelldata;

char	*ft_myjoin(const char *s1, const char *s2, const char *s3);
void	execute_command(t_cmd *cmd, t_shelldata *shell, int i);

int		handle_builtin_command(t_shelldata *shell, char **args);
int		execute_builtin(t_shelldata *shell, char **args);
int		check_builtin_and_path(t_cmd *cmd, t_shelldata *shell);
int		is_file_dir_name(const char *file);
void	display_error_messages(t_cmd *cmds);	
int		is_simple_unset_command(t_cmd *cmd, t_shelldata *shell);
int		is_simple_cd_command(t_cmd *cmd, t_shelldata *shell);
int		is_simple_export_command(t_cmd *cmd, t_shelldata *shell);
int		check_pipe_error(t_shelldata *data);
void	close_files(t_cmd **cmds);

#endif
