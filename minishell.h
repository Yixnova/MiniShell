/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/21 10:11:54 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_tokens
{
	int				type;
	char			*content;
	struct s_tokens	*next;
}	t_tokens;

typedef struct s_shelldata
{
	char		*input;
	t_tokens	*tokens;
}	t_shelldata;

typedef	struct s_vars
{
	char			*name;
	char			*value;
	struct s_vars	*next;
} t_vars;

typedef	struct s_shelldata
{
	char		*input;
	char		**tokens_arr;
	t_vars		*variables;
} t_shelldata;

int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

#endif
