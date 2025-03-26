/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:09:33 by busseven          #+#    #+#             */
/*   Updated: 2025/03/26 11:32:34 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	copy_word_noquotes(char *dest, const char *src)
{
	int	i;
	int	k;
	int	in_quotes;
	int	type;

	i = 0;
	k = 0;
	in_quotes = 0;
	while (src[i])
	{
		if (src[i] == 39 || src[i] == 34)
		{
			if (in_quotes == 0)
			{
				in_quotes = 1;
				type = src[i];
				i++;
			}
			else if (in_quotes == 1 && type == src[*i])
			{
				in_quotes = 0;
				i++;
			}
		}
		dest[k] = src[i];
		i++;
	}
}

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

//removes quotes from a string, frees the string and returns the edited string.
char	*remove_quotes(char *str)
{
	int		len;
	char	*copy;

	len = get_len_without_quotes(str);
	copy = ft_calloc(len + 1, sizeof(char));
	copy_word_noquotes(copy, str);
	if(str)
		free(str);
	return(copy);
}