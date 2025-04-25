/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:15 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/22 10:12:23 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	exit_command(char **args, t_shelldata *shell)
{
	int	status;
	int	is_num;

	status = 0;
	is_num = 1;
	if (args[1])
	{
		is_num = is_numeric(args[1]);
		if (!is_num)
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			free_shell_data(shell);
			exit(255);
		}
		if (args[2])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			shell->exit_status = 1;
			return ;
		}
		status = ft_atoi(args[1]);
	}
	free_shell_data(shell);
	exit(status);
}
