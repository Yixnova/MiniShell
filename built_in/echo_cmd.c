/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:33:26 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 19:06:50 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	line_check(char **arg)
{
	int	i;
	int	j;

	i = 1;
	while (arg[i] && arg[i][0] == '-' && arg[i][1] == 'n')
	{
		j = 1;
		while (arg[i][j] == 'n')
			j++;
		if (arg[i][j] != '\0')
			break ;
		i++;
	}
	return (i - 1);
}

void	echo_command(char **arg)
{
	int	i;
	int	no_line;

	no_line = line_check(arg);
	i = no_line + 1;
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (arg[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (no_line == 0)
		printf("\n");
}
