/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsedata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 10:31:23 by busseven          #+#    #+#             */
/*   Updated: 2025/04/21 13:53:59 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	find_command_path(t_cmd *cmd, t_shelldata *shell)
{
	if (check_builtin_and_path(cmd, shell))
		return (1);
	if (search_in_paths(cmd, shell))
		return (1);
	return(0);
}

void	check_files_and_commands(t_shelldata *data, t_cmd *cmd)
{
	while(cmd)
	{
		pick_pipes(cmd);
		open_files(cmd);
		pick_file_descriptors(cmd);
		if(!find_command_path(cmd, data))
			cmd->invalid = 1;
		cmd = cmd->next;
	}
}

void	init_parsedata(t_shelldata *shell)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while(shell->tokens[i])
	{
		if(ft_strlen(shell->tokens[i]) == 1 && shell->tokens[i][0] == '|')
			count++;
		i++;
	}
	shell->cmds = ft_calloc(count + 1, sizeof(t_cmd *));
	shell->cmd_count = count + 1;
	while(count + 1 > 0)
	{
		add_cmd(shell, ft_cmdnew());
		count--;
	}
}
