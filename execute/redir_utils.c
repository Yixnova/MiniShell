/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 19:10:55 by busseven          #+#    #+#             */
/*   Updated: 2025/05/12 14:50:38 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	r_len(char *str)
{
	if (redir_num(str) == 1 || redir_num(str) == 4)
		return (1);
	if (redir_num(str) == 2 || redir_num(str) == 3)
		return (2);
	return (0);
}

void	not_here_doc(t_cmd *cmd, int i, int f)
{
	if (redir_num(cmd->redirs[i]) == 2 || redir_num(cmd->redirs[i]) == 1)
	{
		cmd->output = cmd->des[f];
		cmd->output_type = 2;
	}
	else if (redir_num(cmd->redirs[i]) == 4)
	{
		cmd->input = cmd->des[f];
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
	char	*file_name;

	i = 0;
	n = 0;
	cmd->des = ft_calloc(cmd->redir_count - cmd->hd_count, sizeof(int));
	while (cmd->redirs[i])
	{
		file_name = expand(cmd->redirs[i] + 1 + r_len(cmd->redirs[i]), shell);
		if (redir_num(cmd->redirs[i]) != 3)
		{
			if (redir_num(cmd->redirs[i]) == 1)
				cmd->des[n] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (redir_num(cmd->redirs[i]) == 2)
				cmd->des[n] = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
			else if (redir_num(cmd->redirs[i]) == 4)
				cmd->des[n] = open(file_name, O_RDONLY);
			if (cmd->des[n] < 0)
				return (open_error(cmd, file_name, redir_num(cmd->redirs[i])));
			n++;
		}
		i++;
	}
	return (0);
}
