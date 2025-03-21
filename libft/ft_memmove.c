/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:51:01 by yigsahin          #+#    #+#             */
/*   Updated: 2024/10/29 15:31:46 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t num)
{
	unsigned char		*dst;
	const unsigned char	*src;

	dst = (unsigned char *)destination;
	src = (const unsigned char *)source;
	if (destination == source)
	{
		return (destination);
	}
	if (src < dst)
	{
		while (num--)
			*(dst + num) = *(src + num);
		return (destination);
	}
	while (num--)
		*dst++ = *src++;
	return (destination);
}
