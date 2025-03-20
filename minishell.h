/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/20 09:31:03 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./ft_printf/ft_printf.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef	struct s_tokens
{
//token types = " ' < > >> << $? $characters=something
	int			type;
	char		*content;
	struct s_tokens 	*next;
}	t_tokens;

typedef	struct s_shelldata
{
	char		*input;
	t_tokens 	*tokens;
}	t_shelldata;

int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);

void	handle_input_and_history(t_shelldata *shelldata);

#endif
