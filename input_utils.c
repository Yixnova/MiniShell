/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:42:30 by busseven          #+#    #+#             */
/*   Updated: 2025/03/20 08:53:03 by yigsahin         ###   ########.fr       */
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
	int	res;

	if (!line)
		res = 1;
	else if (line[0] == '\0')
		res = 1;
	else
		res = is_all_spaces(line);
	return (res);
}
