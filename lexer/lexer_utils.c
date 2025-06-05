/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:36:13 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:38 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

char	*copy_redirs(char	*str, int	*n)
{
	int		i;
	char	*ret;

	i = *n;
	while (is_in_str("<>", str[*n]))
		(*n)++;
	ret = ft_substr(str, i, (*n) - i);
	return (ret);
}

int	assign_word_to_array(char **arr, char *str, int *i, int *n)
{
	if (is_in_str("|", str[*n]))
	{
		arr[*i] = char_to_str(str[*n]);
		(*n)++;
	}
	else if (is_in_str("<>", str[*n]))
	{
		arr[*i] = copy_redirs(str, n);
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
