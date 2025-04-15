/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/15 12:40:45 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_token_arr(char **token_arr)
{
	int	i;

	if (!token_arr)
		return ;
	i = 0;
	while (token_arr[i])
	{
		free(token_arr[i]);
		i++;
	}
	free(token_arr);
}

void	tokenize_input(t_shelldata *data)
{
	data->tokens = split_into_words(data->input);
	if (!data->tokens)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return ;
	}
}
