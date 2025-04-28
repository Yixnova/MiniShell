/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:09:33 by busseven          #+#    #+#             */
/*   Updated: 2025/04/28 12:14:59 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

static int handle_quotes(int *i, int *in_quotes, int *type, const char *src)
{
	if (src[*i] == 39 || src[*i] == 34)
	{
		if (*in_quotes == 0)
		{
			*in_quotes = 1;
			*type = src[*i];
			(*i)++;
			return (1);
		}
		else if (*in_quotes == 1 && *type == src[*i])
		{
			*in_quotes = 0;
			(*i)++;
			return (1);
		}
		else 
			return (0);
	}
	return (0);
}
static void	copy_word_noquotes(char *dest, const char *src)
{
	int	i;
	int	k;
	int	in_quotes;
	int	type;

	i = 0;
	k = 0;
	in_quotes = 0;
	while (src[i])
	{
		if (src[i] == 39 || src[i] == 34)
		{
			if(!handle_quotes(&i, &in_quotes, &type, src))
				dest[k++] = src[i++];
		}
		else
			dest[k++] = src[i++];
	}
}

static int	handle_quote_logic(int *in_quotes, int *type, char current_char)
{
	if (*in_quotes == 0)
	{
		*in_quotes = 1;
		*type = current_char;
	}
	else if (*in_quotes == 1 && *type == current_char)
		*in_quotes = 0;
	else
		return (1);
	return (0);
}

static int	get_len_without_quotes(const char *str)
{
	int		type;
	int		i;
	int		in_quotes;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (!handle_quote_logic(&in_quotes, &type, str[i]))
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*remove_quotes(char *str)
{
	int		len;
	char	*copy;

	len = get_len_without_quotes(str);
	copy = ft_calloc(len + 1, sizeof(char));
	copy_word_noquotes(copy, str);
	return (copy);
}
