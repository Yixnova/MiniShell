/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/30 13:42:10 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	continue_quoted_input(t_shelldata *data, int type)
{
	char	*line;
	char	*type_str;

	data->input = ft_join(data->input, "\n");
	while(1)
	{
		line = ft_join(readline(">"), "\n");
		data->input = ft_join(data->input, line);
		if(is_in_str(line, type))
			break;
		else if(!line)
		{
			write(2, "minishell: ", 11);
			write(2, "unexpected EOF while looking for matching \"", 44);
			write(2, &type, 1);
		}
	}
	check_unclosed_quotes(data);
}
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
void	check_unclosed_quotes(t_shelldata *data)
{
	int	type;
	int	in_quotes;
	int	i;

	i = 0;
	type = 0;
	in_quotes = 0;
	while(data->input[i])
	{
		if(data->input[i] == 34 || data->input[i] == 39)
		{
			if(in_quotes == 0)
			{
				type = data->input[i];
				in_quotes = 1;
			}
			else if(in_quotes == 1 && data->input[i] == type)
			{
				in_quotes = 0;
			}
		}
		i++;
	}
	if(in_quotes = 1);
		continue_quoted_input(data, type);
	else
		return ;
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
	check_unclosed_quotes(data)
	if(check_pipe_error(data))
		return (1);
	return (0);
}
