/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:31:18 by yigsahin          #+#    #+#             */
/*   Updated: 2024/10/29 15:32:21 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	compare(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*ptr;
	size_t	i;
	size_t	slen;

	i = 0;
	slen = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (compare(*s1, set) && *s1)
	{
		s1++;
		slen -= 1;
	}
	while (slen > 0 && compare(s1[slen - 1], set))
		slen -= 1;
	ptr = (char *) malloc (sizeof(char) * slen + 1);
	if (!ptr)
		return (NULL);
	while (i < slen)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
