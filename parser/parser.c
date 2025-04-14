/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 13:26:23 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	open_here_document(t_cmd *cmd, int h)
{
	char	*line;

	while(1)
	{
		line = readline("> ");
		if(!line)
			break ;
		if(!ft_strncmp(line, cmd->limiter_arr[h], ft_strlen(line)))
			break ;
		else
			write(cmd->hd_arr[h][1], line, ft_strlen(line));
	}
	close(cmd->hd_arr[h][1]);
}
void	make_here_documents(t_cmd *cmd)
{
	int	h;
	int	count;

	h = 0;
	count = 0;
	while(cmd)
	{
		while(cmd->limiter_arr[count])
			count++;
		printf("hd count: %d\n", count);
		cmd->hd_arr = ft_calloc(count + 1, sizeof(int *));
		while(count > 0)
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
void	free_2d_char(char **arr)
{
	int	i;

	i = 0;
	if(!arr)
		return ;
	while(arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_cmd_arr(t_cmd	**cmds)
{
	t_cmd	*temp;

	while(*cmds)
	{
		temp = (*cmds)->next;
		free_2d_char((*cmds)->tokens);
		free_2d_char((*cmds)->args);
		free_2d_char((*cmds)->redirs);
		free_2d_char((*cmds)->limiter_arr);
		free(*cmds);
		*cmds = temp;
	}
}
int	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	cmd->tokens = ft_calloc(*n - *i + 2, sizeof(char *));
	while(shell->tokens && shell->tokens[*i] && *i < *n)
	{
		cmd->tokens[k] = ft_strdup(shell->tokens[*i]);
		k++;
		(*i)++;
	}
	make_arg_array(cmd, shell);
	make_redir_array(cmd, shell);
	int o = 0;
	while(cmd->redirs[o])
	{
		printf("redir:%s\n", cmd->redirs[o]);
		o++;
	}
	make_limiter_arr(cmd);
	o = 0;
	while(cmd->limiter_arr[o])
	{
		printf("lim:%s\n", cmd->limiter_arr[o]);
		o++;
	}
	printf("checking errors:");
	if(check_parse_errors(cmd))
		return (1);
	pipe(cmd->pipe);
	printf("next cmd:\n");
	return (0);
}

int	edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	if (!cmds)
	{
		printf("no cmd\n");
		return (0);
	}
	while (shell->tokens && shell->tokens[n] && !is_pipe(shell->tokens[n]))
		n++;
	if(init_cmd(shell, cmds, &i, &n))
	{
		free_cmd_arr(shell->cmds);
		return (1);
	}
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
	make_here_documents(cmds);
	return (0);
}
