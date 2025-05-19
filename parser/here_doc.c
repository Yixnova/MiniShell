/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:23:39 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 19:37:41 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	heredoc_parent()
{
	int	status;

	signal(SIGINT, SIG_IGN);
	wait(&status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		g_signal_flag = 1;
	setup_signals();
}

static char	*get_line(t_shelldata *shell, t_cmd *cmd, int h)
{
	char	*new_line;

	new_line = readline("> ");
	if (cmd->hd_parsedollar[h] && new_line)
	{
		new_line = expand(new_line, shell, 1);
	}
	return(new_line);
}

static void	open_here_document(t_cmd *cmd, int h, t_shelldata *shell)
{
	char	*line;
	int		line_num;

	line_num = 1;
	while (1)
	{
		line = get_line(shell, cmd, h);
		if (!line)
			heredoc_eof(cmd, line_num, h, line);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
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
void	heredoc_child(t_cmd *cmd, t_shelldata *shell)
{
	int	h;
	int	count;


	setup_heredoc_signals();
	h = 0;
	count = cmd->hd_count;
	while (cmd)
	{
		while (count > 0)
		{
			open_here_document(cmd, h, shell);
			count--;
			h++;
		}
		cmd = cmd->next;
	}
}

void	make_cmd_heredocs(t_cmd *cmd, t_shelldata *shell)
{
	int	h;
	int	count;
	int	pid;

	h = 0;
	if (!cmd || !cmd->limiter_arr)
		return ;
	if (cmd->hd_count <= 0)
		return ;
	count = cmd->hd_count;
	cmd->hd_arr = ft_calloc(cmd->hd_count, sizeof(int *));
	while(count > 0)
	{
		cmd->hd_arr[h] = ft_calloc(2, sizeof(int));
		pipe(cmd->hd_arr[h]);
		count--;
		h++;
	}
	pid = fork();
	if(pid != 0)
		return(heredoc_parent());
	else
		return(heredoc_child(cmd, shell));
	exit(0);
}
