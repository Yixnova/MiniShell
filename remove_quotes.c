/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:09:33 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 11:10:06 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		get_len_without_quotes(const char *str)
{
	int		type;
	int		i;
	int		in_quotes;
	int		len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (in_quotes == 0)
			{
				in_quotes = 1;
				type = str[i];
			}
			else if (in_quotes == 1 && type == str[i])
				in_quotes = 0;
			else
				len++;
		}
		else
			len++;
		i++;
	}
	return (len);
}

char	*copy_quotes_removed(const char *str)
{
	int		len;
	char	*copy;

	len = get_len_without_quotes(str);
	copy = ft_calloc(len + 1, sizeof(char));
}