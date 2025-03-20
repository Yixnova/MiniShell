/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/20 14:38:39 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>


typedef struct s_shelldata
{
	char		*input;
	char		**tokens;
}	t_shelldata;


int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

#endif
