/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:23:39 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 17:06:43 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_here_document(t_cmd *cmd, int h)
{
	char	*line;
	int		line_num;

	line_num = 0;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("warning: ");
			printf("here-document at line %d", line_num);
			printf("delimited by end-of-file (wanted `%s')", line);
			break;
		}
		if (!ft_strncmp(line, cmd->limiter_arr[h], ft_strlen(line)))
			break ;
		else
			write(cmd->hd_arr[h][1], line, ft_strlen(line));
		line_num++;
	}
	close(cmd->hd_arr[h][1]);
}

void	make_cmd_heredocs(t_cmd *cmd)
{
	int	h;
	int	count;

	h = 0;
	count = 0;
	while (cmd->limiter_arr[count])
		count++;
	cmd->hd_arr = ft_calloc(count + 1, sizeof(int *));
	while (cmd)
	{
		while (count > 0)
		{
			cmd->hd_arr[h] = ft_calloc(2, sizeof(int));
			pipe(cmd->hd_arr[h]);
			open_here_document(cmd, h);
			count--;
			h++;
		}
		cmd = cmd->next;
	}
}
void	open_all_heredoc(t_cmd *cmd)
{
	while(cmd)
	{
		make_cmd_heredocs(cmd);
		cmd = cmd->next;
	}
}
