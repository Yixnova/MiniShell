/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 13:55:12 by busseven          #+#    #+#             */
/*   Updated: 2025/03/05 11:48:52 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_unbr(unsigned int n, int fd)
{
	char	c;
	int		ret;

	ret = 0;
	if (n > 9)
	{
		ret += ft_print_unbr(n / 10, fd);
		ret += ft_print_unbr(n % 10, fd);
	}
	else if (n <= 9)
	{
		c = '0' + n;
		write(fd, &c, 1);
		ret++;
	}
	return (ret);
}
