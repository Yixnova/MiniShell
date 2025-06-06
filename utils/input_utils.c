/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:42:30 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:13:09 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*char_to_str(char c)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = c;
	str[1] = '\0';
	return (str);
}

int	is_in_str(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	is_space_character(char c)
{
	return (c == ' ' || (c >= 7 && c <= 13));
}

int	is_all_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space_character(line[i])
			|| line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	int	res;

	if (!line)
		res = 1;
	else if (line[0] == '\0')
		res = 1;
	else
		res = is_all_spaces(line);
	return (res);
}
