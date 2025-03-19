/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:42:30 by busseven          #+#    #+#             */
/*   Updated: 2025/03/19 14:43:11 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space_character(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_all_spaces(char *line)
{
	int	i;
	i = 0;
	
	while (line[i])
	{
		if (!is_space_character(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_empty_line(char *line)
{
	return (!line || line[0] == '\0' || is_all_spaces(line));
}