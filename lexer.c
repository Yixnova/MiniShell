/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/03/25 14:29:19 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	tokenize_input(t_shelldata	*data)
{
	data->token_arr = split_into_words(data->input, data);
	//expander buraya gelecek
	int k = 0;
	while (data->token_arr[k])
	{
		printf("%s\n", data->token_arr[k]);
		k++;
	}
}