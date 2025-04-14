/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:33:26 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/14 14:48:56 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

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

void	free_arguments(char **arg)
{
	int	i;

	if (!arg)
		return ;
	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
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
	free_arguments(arg);
}
