/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 20:21:25 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tokenize_input(t_shelldata	*data)
{
	data->token_arr = split_into_words(data->input);
	//expander buraya gelecek
	int k = 0;
	while (data->token_arr[k])
	{
		data->token_arr[k] = remove_quotes(data->token_arr[k]);
		k++;
	}
}
