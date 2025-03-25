/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_expander.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:14:57 by busseven          #+#    #+#             */
/*   Updated: 2025/03/25 12:17:44 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

char	*ft_substr_env(char const *s, unsigned int start, unsigned int end)
{
	char	*sub_str;
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = get_len();
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