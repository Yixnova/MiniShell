/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 20:06:49 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

void	handle_special_characters(char *str, int *on_word, int *i, int *count)
{
	*on_word = 0;
	if (is_in_str("<>", str[*i]))
	{
		while (str[*i] && is_in_str("<>", str[*i]))
			(*i)++;
		(*i)--;
	}
	(*count)++;
}

void	skip_in_quotes(char	*str, int *i, int type)
{
	if (str[*i] == 39 || str[*i] == 34)
	{
		while (str[*i])
		{
			(*i)++;
			if (str[*i] == type)
				return ;
		}
	}
}

int	count_words(char *str)
{
	int	i;
	int	on_word;
	int	count;

	count = 0;
	on_word = 0;
	i = 0;
	while (str && str[i])
	{
		if (is_space_character(str[i]))
			on_word = 0;
		else if (is_in_str("<>|", str[i]))
			handle_special_characters(str, &on_word, &i, &count);
		else if (on_word == 0)
		{
			on_word = 1;
			count++;
		}
		skip_in_quotes(str, &i, str[i]);
		i++;
		if (i > (int)ft_strlen(str) - 1)
			break ;
	}
	return (count);
}

char	**split_into_words(char *str)
{
	char	**arr;
	int		i;
	int		n;

	arr = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	n = 0;
	while (i < count_words(str))
	{
		while (str[n] && is_space_character(str[n]))
			n++;
		if (!assign_word_to_array(arr, str, &i, &n))
			return (NULL);
	}
	return (arr);
}
