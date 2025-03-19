/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:13:48 by busseven          #+#    #+#             */
/*   Updated: 2025/03/05 11:50:14 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
#include <unistd.h>

int	ft_printf(const char *s, ...);
int	ft_print_char(char c);
int	ft_print_str(char *s);
int	ft_print_nbr(int i);
int	ft_print_hex(int i, char s);
int	ft_print_ptr(void *p);
int	ft_print_unbr(unsigned int n, int fd);
int	ft_print_percent(void);

#endif