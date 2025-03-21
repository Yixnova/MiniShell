/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:19:30 by yigsahin          #+#    #+#             */
/*   Updated: 2024/10/29 15:31:01 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total;
	size_t	i;

	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
		((unsigned char *)ptr)[i++] = 0;
	return (ptr);
}
