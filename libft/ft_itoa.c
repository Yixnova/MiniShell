/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 17:34:01 by yigsahin          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:57 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(long num)
{
	int	digits;

	digits = 1;
	if (num < 0)
	{
		num *= -1;
	}
	while (num > 9)
	{
		num /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		digits;
	long	num;
	int		sign;

	num = n;
	sign = 0;
	digits = count_digits(num);
	if (num < 0 && ++digits)
	{
		num *= -1;
		sign = -1;
	}
	number = (char *) malloc (sizeof(char) * digits + 1);
	if (!number)
		return (NULL);
	number[digits] = 0;
	while (digits)
	{
		number[digits-- - 1] = (num % 10) + 48;
		num /= 10;
	}
	if (sign == -1)
		number[0] = '-';
	return (number);
}
