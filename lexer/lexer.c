/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/19 15:09:51 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

int	check_pipe_error(t_shelldata *data, int *i)
{
	if(!data->tokens)
		return (0);
	while(data->tokens && data->tokens[*i])
	{
		if(is_pipe(data->tokens[*i]))
		{
			(*i)++;
			while(data->tokens[*i] && is_redir(data->tokens[*i]))
				(*i)++;
			if(data->tokens[*i] && is_pipe(data->tokens[*i]))
			{
				printf("pipe error\n");
				return (1);
			}
		}
		(*i)++;
	}
	while(!data->tokens[*i])
		(*i)--;
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
	int		i;
	char	*line;

	i = 0;
	data->tokens = split_into_words(data->input);
	if(check_pipe_error(data, &i))
		return (1);
	if (data->tokens[i] && is_pipe(data->tokens[i]))
	{
		line = readline("> ");
		data->input = ft_join(data->input, line);
		free_2d_char(data->tokens);
		data->tokens = split_into_words(data->input);
	}
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return (1);
	}
	return (0);
}
