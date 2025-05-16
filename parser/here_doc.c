/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:23:39 by busseven          #+#    #+#             */
/*   Updated: 2025/05/16 14:40:56 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*get_line(t_shelldata *shell, t_cmd *cmd, int h)
{
	if (cmd->hd_parsedollar[h])
		return (expand(readline("> "), shell, 1));
	else
		return (readline("> "));
}

static void	heredoc_eof(t_cmd *cmd, int line_num, int h, char *line)
{
	close(cmd->hd_arr[h][1]);
	printf("warning: ");
	printf("here-document at line %d ", line_num);
	printf("delimited by end-of-file (wanted `%s')\n", cmd->limiter_arr[h]);
	free(line);
}

static void	open_here_document(t_cmd *cmd, int h, t_shelldata *shell)
{
	char	*line;
	int		line_num;

	line_num = 0;
	while (1)
	{
		line = get_line(shell, cmd, h);
		if (!line)
		{
			heredoc_eof(cmd, line_num, h, line);
			break ;
		}
		if (line[0] == '\0')
			continue ;
		if (!ft_strncmp(line, cmd->limiter_arr[h], ft_strlen(line)))
		{
			free(line);
			close(cmd->hd_arr[h][1]);
			break ;
		}
		write(cmd->hd_arr[h][1], line, ft_strlen(line));
		write(cmd->hd_arr[h][1], "\n", 1);
		line_num++;
		free(line);
	}
}

void	make_cmd_heredocs(t_cmd *cmd, t_shelldata *shell)
{
	int	h;
	int	count;

	h = 0;
	if (!cmd || !cmd->limiter_arr)
		return ;
	if (cmd->hd_count <= 0)
		return ;
	count = cmd->hd_count;
	cmd->hd_arr = ft_calloc(cmd->hd_count, sizeof(int *));
	while (cmd)
	{
		while (count > 0)
		{
			cmd->hd_arr[h] = ft_calloc(2, sizeof(int));
			pipe(cmd->hd_arr[h]);
			open_here_document(cmd, h, shell);
			count--;
			h++;
		}
		cmd = cmd->next;
	}
}
