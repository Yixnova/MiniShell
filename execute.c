/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 20:38:29 by yigsahin          #+#    #+#             */
/*   Updated: 2025/03/26 13:54:43 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

void	execute_command(t_shelldata *shell)
{
	char	**args;

	args = ft_split(shell->input, ' ');
	if (!args || !args[0])
	{
		ft_putendl_fd("Error: Failed to parse input.", 2);
		return ;
	}
	if (ft_strncmp(args[0], "env", 4) == 0)
		env_command(shell->env, args);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		echo_command(args);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		cd_command(args[1]);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		pwd();
	else if (ft_strncmp(args[0], "export", 7) == 0)
		export_command(&(shell->env), args);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		unset_command(&(shell->env), args);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		exit_command(args, shell);
	else
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(shell->input, 2);
	}
}
