/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 17:56:36 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int	syntax_error(char *token)
{
	write(2, "minishell: ", 12);
	write(2, "syntax_error in token: ", 24);
	write(2, token, ft_strlen(token));
	write(2, "\n", 1);
	return (1);
}
