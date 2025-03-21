/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/03/21 16:15:43 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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
		if (!is_space_character(str[i]))
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
void	tokenize_input(t_shelldata	*data)
{
	printf("%d\n", count_words(data->input));
}