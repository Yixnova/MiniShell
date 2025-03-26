/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 09:31:58 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_in_quotes(char	*str, int *i, int type)
{
	while (str[*i])
	{
		(*i)++;
		if (str[*i] == type)
			return ;
	}
	unclosed_quotes();
}
int	count_words(char *str, t_shelldata *data)
{
	int	i;
	int	count;
	
	count = 0;
	i = 0;
	while (str[i])
	{
		if (is_space_character(str[i]))
			data->on_word = 0;
		else if (is_in_str("<>|", str[i]))
		{
			data->on_word = 0;
			count++;
		}
		else if (data->on_word == 0)
		{
			data->on_word = 1;
			count++;
		}
		if (str[i] == 39 || str[i] == 34)
			skip_in_quotes(str, &i, str[i]);
		i++;
	}
	return (count);
}
void	handle_quotes(char *str, int *i, t_shelldata *data)
{
	if(str[*i] == 39 || str[*i] == 34)
	{
		if(data->in_quotes == 0)
		{
			data->in_quotes = 1;
			data->type = str[*i];
		}
		else if(data->in_quotes == 1 && data->type == str[*i])
			data->in_quotes = 0;
	}
}

char	*copy_word(char *str, int *n, t_shelldata *data)
{
	char	*word;
	int		i;

	i = (*n);
	while (str[i])
	{
		handle_quotes(str, &i, data);
		if(data->in_quotes == 0 && is_in_str(" <>|", str[i]))
			break;
		i++;
	}
		i++;
	word = ft_substr(str, *n, i - *n - 1);
	*n = i - 1;
	return (word);
}

char	**split_into_words(char *str, t_shelldata *data)
{
	char	**arr;
	int		i;
	int		n;

	arr = ft_calloc(count_words(str, data) + 1, sizeof(char *));
	i = 0;
	n = 0;
	printf("%d\n", count_words(str, data));
	while (i < count_words(str, data))
	{
		while (str[n] && is_space_character(str[n]))
			n++;
		if(is_in_str("><|", str[n]))
		{
			arr[i] = char_to_str(str[n]);
			n++;
		}
		else
			arr[i] = copy_word(str, &n, data);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
