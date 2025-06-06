/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:31:29 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_FUNCTIONS_H
# define FREE_FUNCTIONS_H

# include "../inc/minishell.h"

void	free_cmds(t_shelldata *shell);
void	free_2d_char(char **arr);
void	free_shell(t_shelldata *shell);
void	free_input_data(t_shelldata *shell);

int		free_buffer(char *buffer, int i);

#endif
