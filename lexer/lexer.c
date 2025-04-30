/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/30 13:11:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	pipe_error(void)
{
	write(2, "Syntax error: invalid use of token '|'\n", 39);
	return (1);
}
int	add_tokens(t_shelldata *data)
{
	char	*line;

	line = readline("> ");
	data->input = ft_join(data->input, line);
	free_2d_char(data->tokens);
	data->tokens = split_into_words(data->input);
	return (0);
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
				return(add_tokens(data));
			else if(is_pipe(data->tokens[i + 1]))
				return(pipe_error());
		}
		i++;
	}
	return (0);
}
void	free_token_arr(char **token_arr)
{
	int	i;

	if (!token_arr)
		return ;
	i = 0;
	while (token_arr[i])
	{
		free(token_arr[i]);
		i++;
	}
	free(token_arr);
}

int	tokenize_input(t_shelldata *data)
{
	data->tokens = split_into_words(data->input);
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (1);
	}
	if(check_pipe_error(data))
		return (1);
	return (0);
}
