/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:14:57 by busseven          #+#    #+#             */
/*   Updated: 2025/03/25 15:32:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

void	handle_quotes_removed(char *str, int *i, int *in_quotes, int *type)
{
	if (str[*i] == 39 || str[*i] == 34)
	{
		if (*in_quotes == 0)
		{
			*in_quotes = 1;
			*type = str[*i];
			*i += 1;
		}
		else if (*in_quotes == 1 && *type == str[*i])
		{
			*in_quotes = 0;
			*i += 1;
		}
	}
}

char	*ft_substr_env(char const *s, unsigned int start, unsigned int end, t_env *env)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = get_len(s, start, end, env);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;
	size_t	slen;

	slen = ft_strlen(s);
	i = 0;
	if (slen <= start)
		return (ft_strdup(""));
	if (slen < start + len)
		len = slen - start;
	sub_str = (char *) malloc (sizeof(char) * len + 1);
	if (!sub_str)
		return (NULL);
	while (i < len)
	{
		sub_str[i] = s[start];
		i++;
		start++;
	}
	sub_str[i] = 0;
	return (sub_str);
}
