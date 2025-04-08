/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/08 14:39:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	tokenize_input(t_shelldata	*data)
{
	int	k;

	k = 0;
	data->token_arr = split_into_words(data->input);
	while (data->token_arr[k])
	{
		data->token_arr[k] = expand_string(data->token_arr[k], data);
		k++;
	}
}
