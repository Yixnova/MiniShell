/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:33:56 by yigsahin          #+#    #+#             */
/*   Updated: 2024/10/29 15:31:44 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*mem;
	char	*mem2;
	size_t	i;

	i = 0;
	mem = (char *)dst;
	mem2 = (char *)src;
	if (!dst && !src)
	{
		return (NULL);
	}
	while (i < n)
	{
		mem[i] = mem2[i];
		i++;
	}
	return (dst);
}
