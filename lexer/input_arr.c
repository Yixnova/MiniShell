/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:55:47 by busseven          #+#    #+#             */
/*   Updated: 2025/05/22 17:33:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	set_input_arr_parsedata(int *n, char *line, t_lineparse *data)
{
	if (data->on_word == 0 && line[*n] != '\n')
		data->on_word = 1;
	if (data->in_quotes == 0 && is_in_str("\"\'", line[*n]))
	{
		data->in_quotes = 1;
		data->type = line[*n];
	}
	else if (data->in_quotes == 1 && line[*n] == data->type)
		data->in_quotes = 0;
	if (data->on_word == 1 && data->in_quotes == 0 && line[*n] == '\n' 
			&& line[*n - 1] != '|' && line[*n - 1] != '\n')
		return (1);
	(*n)++;
	return (0);
}


void	handle_quotes_count(t_lineparse *data, char *line, int *i)
{
	if (data->in_quotes == 0 && is_in_str("\"\'", line[*i]))
	{
		data->in_quotes = 1;
		data->type = line[*i];
	}
	else if (data->in_quotes == 1 && line[*i] == data->type)
		data->in_quotes = 0;
}

int		count_inputs(char *line)
{
	int			i;
	t_lineparse	data;

	i = 0;
	data.count = 0;
	data.in_quotes = 0;
	data.type = 0;
	data.on_word = 0;
	while (line[i])
	{
		if (data.on_word == 0 && line[i] != '\n')
		{
			data.on_word = 1;
			data.count++;
		}
		if (data.on_word == 1 && data.in_quotes == 0 && line[i] == '\n' 
			&& line[i - 1] != '|' && line[i - 1] != '\n')
			data.on_word = 0;
		i++;
	}
	return (data.count);
}

char	**make_input_arr(char	*line)
{
	char		**arr;
	int			i;
	int			n;
	t_lineparse	data;

	i = 0;
	n = 0;
	data.type = 0;
	data.in_quotes = 0;
	data.start = 0;
	data.count = count_inputs(line);
	arr = ft_calloc(data.count + 1, sizeof(char *));
	while (data.count - 1 >= 0)
	{
		data.on_word = 0;
		data.start = n;
		while (line[n])
			if (set_input_arr_parsedata(&n, line, &data))
				break ;
		arr[i] = ft_substr(line, data.start, n - data.start + 2);
		arr[i] = edit_input(arr[i]);
		i++;
		data.count--;
	}
	return (arr);
}
