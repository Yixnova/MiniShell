/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:45:59 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/30 09:25:20 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd		t_cmd;
typedef struct s_shelldata	t_shelldata;

char	*ft_threejoin(const char *s1, const char *s2, const char *s3);
void	execute_command(t_cmd *cmd, t_shelldata *shell, int i);

int		handle_builtin_command(t_shelldata *shell, char **args);
int		execute_builtin(t_shelldata *shell, char **args);
int		check_builtin_and_path(t_cmd *cmd, t_shelldata *shell);
void	display_error_messages(t_cmd *cmds);
void	close_files(t_cmd **cmds);
void	close_pipes(t_shelldata *shell, int i);
void	start_processes(t_shelldata *shell, t_cmd **cmds);
void	pick_pipes(t_cmd *cmd);
void	pick_file_descriptors(t_cmd *cmd);
int		open_files(t_cmd *cmd, t_shelldata *shell);
int		search_in_paths(t_cmd *cmd, t_shelldata *shell);
int		find_command_path(t_cmd *cmd, t_shelldata *shell);
void	check_files_and_path(t_cmd *cmd, t_shelldata *shell, int pid);

#endif
