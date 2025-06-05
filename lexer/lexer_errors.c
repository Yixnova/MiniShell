/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:51:23 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:37 by yigsahin         ###   ########.fr       */
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
