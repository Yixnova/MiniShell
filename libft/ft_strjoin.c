/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:21:22 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:12:30 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	ptrlen;
	int		i;

	i = 0;
	ptrlen = ft_strlen(s1) + ft_strlen(s2) + 1;
	ptr = (char *) malloc (sizeof(char) * ptrlen);
	if (!ptr)
		return (NULL);
	while (*s1)
	{
		ptr[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		ptr[i] = *s2;
		s2++;
		i++;
	}
	ptr[i] = 0;
	return (ptr);
}
