/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:54:04 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 18:58:22 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <stddef.h>
# include <signal.h>
# include <sys/stat.h>
# include "../libft/libft.h"
# include "built_in.h"
# include <readline/readline.h>
# include <readline/history.h>

# define BUFFER_SIZE 1024

typedef struct s_env
{
	char		*key;
	char		*value;
	struct s_env	*next;
}	t_env;

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
	t_env		*env;
}	t_shelldata;

int		is_space_character(char c);
int		is_all_spaces(char *line);
int		is_empty_line(char *line);

void	handle_input_and_history(t_shelldata *shelldata);
void	free_shell_data(t_shelldata *shelldata);
void	sigint_handler(int signum);
void	setup_signals(void);

void	execute_command(t_shelldata *shell);

#endif
