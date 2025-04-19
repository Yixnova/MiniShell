/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:45:59 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/19 13:34:52 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_cmd		t_cmd;
typedef struct s_shelldata	t_shelldata;

void	array_free(char **arr);
char	*ft_myjoin(const char *s1, const char *s2, const char *s3);
void	execute_command(t_cmd *cmd, t_shelldata *shell, int i);
int		handle_builtin_command(t_shelldata *shell, char **args);

void	find_command_path(t_cmd *cmd, t_shelldata *shell);

#endif
