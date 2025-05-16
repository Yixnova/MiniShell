/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 15:37:48 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	syntax_error_invalid_token(char *token, t_shelldata *data)
{
	ft_putstr_fd("Syntax error: invalid use of token: ", 2);
	ft_putstr_fd(token, 2);
	ft_putchar_fd('\n', 2);
	data->exit_status = 2;
	add_history(data->input);
	return (1);
}
int	add_tokens(t_shelldata *data)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		syntax_error_eof();
		exit(2);
	}
	data->input = ft_strjoin(data->input, " ");
	data->input = ft_join(data->input, line);
	free_2d_char(data->tokens);
	data->tokens = split_into_words(data->input);
	free(line);
	return (0);
}

int	check_unclosed_quotes(char *str)
{
	int	type;
	int	in_quotes;
	int	i;

	i = 0;
	type = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (in_quotes == 0)
			{
				type = str[i];
				in_quotes = 1;
			}
			else if (in_quotes == 1 && str[i] == type)
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
		data->input = ft_myjoin(data->input, "\n", line);
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
	char	*invalid_token;
	int		i;

	i = 0;
	data->tokens = split_into_words(data->input);
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (1);
	}
	invalid_token = check_token_errors(data->tokens);
	if(invalid_token)
		return(syntax_error_invalid_token(invalid_token, data));
	while(data->tokens[i])
		i++;
	i--;
	while(data->tokens[i] && check_unclosed_quotes(data->tokens[i]))
	{
		i = 0;
		invalid_token = check_token_errors(data->tokens);
		if(invalid_token)
			return(syntax_error_invalid_token(invalid_token, data));
		while(data->tokens[i])
			i++;
		i--;
		if(data->tokens[i] && check_unclosed_quotes(data->tokens[i]))
		{
			if(continue_quoted_input(data, check_unclosed_quotes(data->tokens[i])))
				return(1);
		}
	}
	i = 0;
	while(data->tokens[i])
	{
		i = 0;
		invalid_token = check_token_errors(data->tokens);
		if(invalid_token)
			return(syntax_error_invalid_token(invalid_token, data));
		while(data->tokens[i])
			i++;
		i--;
		if(data->tokens[i] && is_pipe(data->tokens[i]))
		{
			add_tokens(data);
		}
		else
			break ;
	}
	add_history(data->input);
	return (0);
}
