/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:06:33 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 14:49:48 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lexing.h"

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
