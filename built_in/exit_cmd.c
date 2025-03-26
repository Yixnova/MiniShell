/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:15 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 19:09:26 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_command(char **args, t_shelldata *shell)
{
	int	status;

	status = 0;
	if (args[1])
		status = ft_atoi(args[1]);
	free_shell_data(shell);
	exit(status);
}
