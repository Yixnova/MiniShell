/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:51:23 by busseven          #+#    #+#             */
/*   Updated: 2025/05/23 12:41:17 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

void	syntax_error_eof(void)
{
	write(2, "minishell: syntax error: unexpected end of file\n", 49);
	write(2, "exit\n", 5);
}

int	pipe_error(void)
{
	write(2, "Syntax error: invalid use of token '|'\n", 39);
	return (1);
}

int	check_pipe_error(t_shelldata *data)
{
	int	i;

	i = 0;
	while (data->tokens[i])
	{
		if (is_pipe(data->tokens[i]))
		{
			if (!data->tokens[i + 1])
				return (2);
			else if (is_pipe(data->tokens[i + 1]))
				return (pipe_error());
		}
		i++;
	}
	return (0);
}

int	quote_error(t_shelldata *data)
{
	ft_putstr_fd("Syntax error: Unclosed quote\n", 2);
	data->exit_status = 2;
	add_history(data->input);
	return (1);
}

int	syntax_error_invalid_token(char *token, t_shelldata *data)
{
	ft_putstr_fd("Syntax error: invalid use of token: ", 2);
	ft_putstr_fd(token, 2);
	ft_putchar_fd('\n', 2);
	data->exit_status = 2;
	add_history(data->input);
	return (1);
}
