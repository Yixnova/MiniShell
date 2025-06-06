/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:13:29 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:13:03 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_2d_char(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

int	is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int	is_redir(char	*str)
{
	if (!str)
		return (0);
	if (str[0] && (str[0] == '<' || str[0] == '>'))
		return (1);
	return (0);
}

int	free_buffer(char *buffer, int i)
{
	if (i)
	{
		free(buffer);
		return (1);
	}
	else
		return (0);
}
