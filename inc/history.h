/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:50:56 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/19 11:52:16 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# include "minishell.h"

# define HISTORY_FILE ".myshell_history"

void	load_history_from_file(void);
void	append_history_to_file(const char *line);
void	save_history_on_exit(void);

#endif
