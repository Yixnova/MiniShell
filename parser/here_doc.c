/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:23:39 by busseven          #+#    #+#             */
/*   Updated: 2025/04/22 18:58:31 by busseven         ###   ########.fr       */
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
			close(cmd->hd_arr[h][1]);
			printf("warning: ");
			printf("here-document at line %d ", line_num);
			printf("delimited by end-of-file (wanted `%s')\n", cmd->limiter_arr[h]);
			break ;
		}
		if(line[0] == '\0')
			continue ;
		if (!ft_strncmp(line, cmd->limiter_arr[h], ft_strlen(line)))
		{
			free(line);
			close(cmd->hd_arr[h][1]);
			break ;
		}
		else
		{
			write(cmd->hd_arr[h][1], line, ft_strlen(line));
			write(cmd->hd_arr[h][1], "\n", 1);
		}
		line_num++;
		free(line);
	}
}
