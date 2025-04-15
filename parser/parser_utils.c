/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 17:13:29 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 16:41:11 by busseven         ###   ########.fr       */
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
	free(arr);
}

int		is_pipe(char *str)
{
	if (!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int		is_redir(char	*str)
{
	if (!str)
		return (0);
	if (str[0] && (str[0] == '<' || str[0] == '>'))
		return (1);
	return (0);
}

int	is_valid_redir(char	*str)
{
	if (!strncmp(str, ">", ft_strlen(str)))
		return (1);
	if (!strncmp(str, ">>", ft_strlen(str)))
		return (2);
	if (!strncmp(str, "<<", ft_strlen(str)))
		return (3);
	if (!strncmp(str, "<", ft_strlen(str)))
		return (4);
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
