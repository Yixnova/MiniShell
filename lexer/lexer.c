/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:41:03 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 09:48:09 by yigsahin         ###   ########.fr       */
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
	int	i;

	data->token_arr = split_into_words(data->input);
	if (!data->token_arr)
	{
		ft_putendl_fd("Error: Memory allocation failed", 2);
		return ;
	}
	i = 0;
	while (data->token_arr[i])
	{
		printf("%s\n", data->token_arr[i]);
		i++;
	}
}
