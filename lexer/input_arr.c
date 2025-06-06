/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_arr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:55:47 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:34 by yigsahin         ###   ########.fr       */
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
		&& !ends_with_pipe(line, *n) && line[*n - 1] != '\n')
		return (1);
	if (line[*n] == '\0')
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

int	count_inputs(char *line)
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
		handle_quotes_count(&data, line, &i);
		if (data.on_word == 0 && line[i] != '\n'
			&& !is_space_character(line[i]))
		{
			data.on_word = 1;
			data.count++;
		}
		if (data.on_word == 1 && data.in_quotes == 0 && line[i] == '\n'
			&& !ends_with_pipe(line, i) && line[i - 1] != '\n')
			data.on_word = 0;
		i++;
	}
	return (data.count);
}

void	assign_arr_element(int n, char **arr, char *line, t_lineparse *data)
{
	arr[data->i] = ft_substr(line, data->start, n - data->start + 1);
	arr[data->i] = edit_input(arr[data->i]);
}

char	**make_input_arr(char	*line)
{
	char		**arr;
	int			n;
	t_lineparse	data;

	data.i = 0;
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
		assign_arr_element(n, arr, line, &data);
		data.i++;
		data.count--;
	}
	arr[data.i] = NULL;
	return (arr);
}
