/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:38:56 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:29 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

typedef struct s_shelldata	t_shelldata;
typedef struct s_cmd		t_cmd;

char	*char_to_str(char c);
char	*ft_join(char	*str, char	*joining);

int		is_in_str(const char *str, char c);
int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);
int		is_pipe(char *str);
int		is_redir(char	*str);
int		is_directory(const char *path);
int		is_builtin_command(const char *cmd);
int		is_simple_unset_command(t_cmd *cmd, t_shelldata *shell);
int		is_simple_cd_command(t_cmd *cmd, t_shelldata *shell);
int		is_simple_export_command(t_cmd *cmd, t_shelldata *shell);
int		is_file_dir_name(const char *file);

int		redir_num(char	*str);
int		redir_len(char *str);

#endif
