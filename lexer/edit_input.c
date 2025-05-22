/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:49:55 by busseven          #+#    #+#             */
/*   Updated: 2025/05/22 12:06:25 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		handle_quotes(int *i, t_lineparse *data, char *str)
{
	if(data->in_quotes == 0 && is_in_str("\"\'", str[*i]))
	{
		data->in_quotes = 1;
		data->type = str[*i];
	}
	else if(data->in_quotes == 1 && str[*i] == data->type)
		data->in_quotes = 0;
	if(data->in_quotes == 0 && str[*i] == '\n' && str[*i - 1] == '\n')
	{
		(*i)++;
		return (1);
	}
	return(0);
}

int		count_input_len(char *str)
{
	int	i;
	int	in_quotes;
	int	count;
	int	type;

	in_quotes = 0;
	type = 0;
	i = 0;
	count = ft_strlen(str);
	while(str[i])
	{
		if(in_quotes == 0 && is_in_str("\"\'", str[i]))
		{
			in_quotes = 1;
			type = str[i];
		}
		if(in_quotes == 1 && str[i] == type)
			in_quotes = 0;
		if(in_quotes == 0 && str[i] == '\n' && str[i - 1] == '|')
			count--;
		i++;
	}
	return (count);
}

char	*edit_input(char	*str)
{
	int		i;
	int		n;
	char	*new;
	t_lineparse	data;

	i = 0;
	data.in_quotes = 0;
	data.type = 0;
	n = 0;
	data.count = count_input_len(str);
	new = ft_calloc(data.count, 1);
	while(str[i] && n < data.count)
	{
		if(handle_quotes(&i, &data, str))
			continue ;
		else if(data.in_quotes == 0 && str[i] == '\n' && str[i - 1] == '|')
			new[n] = ' ';
		else
			new[n] = str[i];
		i++;
		n++;
	}
	new[n] = '\0';
	free(str);
	return (new);
}
