/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:49:55 by busseven          #+#    #+#             */
/*   Updated: 2025/05/26 20:54:27 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		is_all_spaces_til(char *str, int i)
{
	if(str[i] == '\n')
		i--;
	while(i > 0 && is_space_character(str[i]))
		i--;
	if(str[i] == '\n')
		return (1);
	return (0);
}
void	check_char(t_lineparse *data, char *str)
{
	if (data->in_quotes == 0 && is_in_str("\"\'", str[data->i]))
	{
		data->in_quotes = 1;
		data->type = str[data->i];
	}
	else if (data->in_quotes == 1 && str[data->i] == data->type)
		data->in_quotes = 0;
	if (data->in_quotes == 0 && str[data->i] == '\n'
		&& data->i > 0 && ends_with_pipe(str, data->i))
		;
	else if (data->in_quotes == 0 && str[data->i] == '\n'
		&& is_all_spaces_til(str, data->i))
		data->count--;
}

void	set_char(t_lineparse *data, int n, char *new, char *str)
{
	if (data->in_quotes == 0 && str[data->i] == '\n'
		&& data->i > 0 && ends_with_pipe(str, n))
		new[n] = ' ';
	else
		new[n] = str[data->i];
}

int	handle_quotes(int *i, t_lineparse *data, char *str)
{
	if (data->in_quotes == 0 && is_in_str("\"\'", str[*i]))
	{
		data->in_quotes = 1;
		data->type = str[*i];
	}
	else if (data->in_quotes == 1 && str[*i] == data->type)
		data->in_quotes = 0;
	if (*i > 0 && data->in_quotes == 0
		&& str[*i] == '\n' && str[*i - 1] == '\n')
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int	count_input_len(char *str)
{
	t_lineparse	data;

	data.in_quotes = 0;
	data.type = 0;
	data.i = 0;
	data.count = ft_strlen(str);
	while (str[data.i])
	{
		check_char(&data, str);
		data.i++;
	}
	return (data.count);
}

char	*edit_input(char	*str)
{
	int			n;
	char		*new;
	t_lineparse	data;

	data.i = 0;
	data.in_quotes = 0;
	data.type = 0;
	n = 0;
	str = ft_strtrim_free(str, "\a\b\n\t\v\f\r");
	data.count = count_input_len(str);
	printf("%d\n", data.count);
	if (data.count < 1)
		free(str);
	new = ft_calloc(data.count + 1, 1);
	while (str[data.i] && n < data.count)
	{
		if (handle_quotes(&data.i, &data, str))
			continue ;
		set_char(&data, n, new, str);
		data.i++;
		n++;
	}
	if (str)
		free(str);
	return (new);
}
