/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:10:55 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 13:59:21 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	not_here_doc(t_cmd *cmd, int i, int f)
{
	if(redir_num(cmd->redirs[i]) == 2 || redir_num(cmd->redirs[i]) == 1)
	{
		cmd->output = cmd->file_descs[f];
		cmd->output_type = 2;
	}
	else if (redir_num(cmd->redirs[i]) == 4)
	{
		cmd->input = cmd->file_descs[f];
		cmd->input_type = 2;
	}
}
void	pick_pipes(t_cmd *cmd)
{
	cmd->input_type = 0;
	cmd->output_type = 0;
	if (cmd->prev)
		cmd->input_type = 1;
	if (cmd->next)
		cmd->output_type = 1;
}
void	pick_file_descriptors(t_cmd *cmd)
{
	int	i;
	int	f;

	i = 0;
	f = 0;
	cmd->hd_index = -1;
	while (cmd->redirs[i])
	{
		if (redir_num(cmd->redirs[i]) != 3)
		{
			not_here_doc(cmd, i, f);
			f++;
		}
		else if(cmd->hd_arr)
		{
			cmd->input_type = 3;
			cmd->hd_index++;
		}
		i++;
	}
}

void	open_files(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*file_name;

	i = 0;
	n = 0;
	cmd->fd_count = cmd->redir_count - cmd->hd_count;
	cmd->file_descs = ft_calloc(cmd->fd_count, sizeof(int));
	while (cmd->redirs[i])
	{
		file_name = cmd->redirs[i] + is_in_str(cmd->redirs[i], ' ');
		if(redir_num(cmd->redirs[i]))
		{
			if (redir_num(cmd->redirs[i]) == 1)
				cmd->file_descs[n] = open(file_name + 1, O_RDWR | O_CREAT | O_TRUNC, 777);
			else if (redir_num(cmd->redirs[i]) == 2)
				cmd->file_descs[n] = open(file_name + 2, O_RDWR | O_CREAT | O_APPEND, 777);
			else if (redir_num(cmd->redirs[i]) == 4)
				cmd->file_descs[n] = open(file_name + 1, O_RDONLY);
			if (cmd->file_descs[n] < 0)
				open_error(file_name);
			n++;
		}
		i++;
	}
}
