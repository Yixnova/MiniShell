/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/02 15:08:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	add_tokens(t_shelldata *data)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		syntax_error_eof();
		exit(2);
	}
	data->input = ft_join(data->input, line);
	free_2d_char(data->tokens);
	data->tokens = split_into_words(data->input);
	return (0);
}

int	check_unclosed_quotes(t_shelldata *data)
{
	int	type;
	int	in_quotes;
	int	i;

	i = 0;
	type = 0;
	in_quotes = 0;
	while (data->input[i])
	{
		if (data->input[i] == 34 || data->input[i] == 39)
		{
			if (in_quotes == 0)
			{
				type = data->input[i];
				in_quotes = 1;
			}
			else if (in_quotes == 1 && data->input[i] == type)
				in_quotes = 0;
		}
		i++;
	}
	if (in_quotes == 1)
		return (type);
	else
		return (0);
}

int	continue_quoted_input(t_shelldata *data, int type)
{
	char	*line;

	data->input = ft_join(data->input, "\n");
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "minishell: ", 11);
			write(2, "unexpected EOF while looking for matching \"\'\n", 46);
			syntax_error_eof();
			return (1);
		}
		data->input = ft_join(data->input, line);
		if (is_in_str(line, type))
			break ;
	}
	free_2d_char(data->tokens);
	data->tokens = split_into_words(data->input);
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
	while (check_unclosed_quotes(data) != 0 || check_pipe_error(data) == 2)
	{
		while (check_unclosed_quotes(data) != 0)
		{
			if (continue_quoted_input(data, check_unclosed_quotes(data)))
				return (1);
		}
		while (check_pipe_error(data) == 2)
			add_tokens(data);
	}
	return (0);
}
