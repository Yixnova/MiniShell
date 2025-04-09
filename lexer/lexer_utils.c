/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:36:13 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/09 12:46:15 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	assign_word_to_array(char **arr, char *str, int *i, int *n)
{
	if (is_in_str("><|", str[*n]))
	{
		arr[*i] = char_to_str(str[*n]);
		(*n)++;
	}
	else
		arr[*i] = copy_word(str, n);
	if (!arr[*i])
	{
		while ((*i)-- > 0)
			free(arr[*i]);
		free(arr);
		return (0);
	}
	(*i)++;
	return (1);
}

char	*copy_word(char *str, int *n)
{
	char	*word;
	int		type;
	int		i;
	int		in_quotes;

	type = 0;
	i = (*n);
	in_quotes = 0;
	while (str[i])
	{
		handle_array_quotes(str, &i, &in_quotes, &type);
		if (in_quotes == 0 && is_in_str(" <>|", str[i]))
			break ;
		i++;
	}
	i++;
	word = ft_substr(str, *n, i - *n - 1);
	*n = i - 1;
	return (word);
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
		unclosed_quotes();
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
	while (str[i])
	{
		if (is_space_character(str[i]))
			on_word = 0;
		else if (is_in_str("<>|", str[i]))
		{
			on_word = 0;
			count++;
		}
		else if (on_word == 0)
		{
			on_word = 1;
			count++;
		}
		skip_in_quotes(str, &i, str[i]);
		i++;
	}
	return (count);
}

void	handle_array_quotes(char *str, int *i, int *in_quotes, int *type)
{
	if (str[*i] == 39 || str[*i] == 34)
	{
		if (*in_quotes == 0)
		{
			*in_quotes = 1;
			*type = str[*i];
		}
		else if (*in_quotes == 1 && *type == str[*i])
			*in_quotes = 0;
	}
}
