/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:10:55 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:11:08 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	get_fd(char *file_name, t_cmd *cmd, int i, int n)
{
	if (redir_num(cmd->redirs[i]) == 1)
		cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redir_num(cmd->redirs[i]) == 2)
		cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	else if (redir_num(cmd->redirs[i]) == 4)
		cmd->file_descs[n] = open(file_name, O_RDONLY);
}

void	not_here_doc(t_cmd *cmd, int i, int f)
{
	if (redir_num(cmd->redirs[i]) == 2 || redir_num(cmd->redirs[i]) == 1)
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
		else if (cmd->hd_arr)
		{
			cmd->input_type = 3;
			cmd->hd_index++;
		}
		i++;
	}
}

int	open_files(t_cmd *cmd, t_shelldata *shell)
{
	int		i;
	int		n;
	char	*expanded;
	char	*file_name;

	i = 0;
	n = 0;
	if (cmd->redir_count - cmd->hd_count <= 0)
		return (0);
	cmd->file_descs = ft_calloc(cmd->redir_count - cmd->hd_count, sizeof(int));
	while (cmd->redirs[i])
	{
		expanded = expand(cmd->redirs[i], shell, 0);
		file_name = expanded + 1 + redir_len(cmd->redirs[i]);
		if (redir_num(cmd->redirs[i]) != 3)
		{
			get_fd(file_name, cmd, i, n);
			if (cmd->file_descs[n] < 0 || is_directory(file_name))
				return (open_error(cmd, file_name, redir_num(cmd->redirs[i])));
			n++;
		}
		free(expanded);
		i++;
	}
	return (0);
}
