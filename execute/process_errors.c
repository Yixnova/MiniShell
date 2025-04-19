/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:53:32 by busseven          #+#    #+#             */
/*   Updated: 2025/04/17 11:40:52 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_error(char *file)
{
	printf("minishell: %s: %s\n", file, strerror(errno));
	exit(errno);
}