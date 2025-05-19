/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:51:23 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 14:03:43 by busseven         ###   ########.fr       */
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
	while(data->tokens[i])
	{
		if(is_pipe(data->tokens[i]))
		{
			if(!data->tokens[i + 1])
				return(2);
			else if(is_pipe(data->tokens[i + 1]))
				return(pipe_error());
		}
		i++;
	}
	return (0);
}
