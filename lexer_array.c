/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/03/24 13:36:19 by busseven         ###   ########.fr       */
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

int	count_words(char *str)
{
	int	i;
	int	on_word;
	int	count;

	i = 0;
	count = 0;
	on_word = 0;
	while  (str[i])
	{
		if (str[i] && !is_space_character(str[i]))
		{
			if (on_word == 0)
			{
				on_word = 1;
				count++;
			}
			if (str[i] == 34 || str[i] == 39)
				skip_in_quotes(str, &i, str[i]);
		}
		else	
			on_word = 0;
		i++;
	}
	return (count);
}

char	*copy_word(char	*str, int *n)
{
	char	*word;
	int		i;

	i = (*n);
	while (str[i] && !is_space_character(str[i]))
		i++;
	word = ft_substr(str, *n, i - *n + 1);
	*n += i - *n;
	return (word);
}
char	*copy_quoted_phrase(char *str, int *n, int type)
{
	char	*word;
	int		i;

	i = (*n) + 1;
	while (str[i] && str[i] != type)
		i++;
	word = ft_substr(str, *n, i - *n + 1);
	*n += i - *n + 1;
	return (word);
}

char	**split_into_words(char *str)
{
	char	**arr;
	int		i;
	int		n;

	arr = ft_calloc(count_words(str) + 1, sizeof(char *));
	i = 0;
	n = 0;
	while (i < count_words(str))
	{
		while (str[n] && is_space_character(str[n]))
			n++;
		if (str[n] && (str[n] == 34 || str[n] == 39))
			arr[i] = copy_quoted_phrase(str, &n, str[n]);
		else
			arr[i] = copy_word(str, &n);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
