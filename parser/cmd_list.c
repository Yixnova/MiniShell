/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/05/10 10:26:47 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_cmdnew(void)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	return (new);
}

void	add_cmd(t_shelldata *shell, t_cmd *new)
{
	t_cmd	*temp;

	if (!*(shell->cmds))
	{
		*(shell->cmds) = new;
		return ;
	}
	temp = *(shell->cmds);
	while (temp->next)
	{
		temp = temp->next;
	}
	temp->next = new;
	new->prev = temp;
}

void	free_cmd_arr(t_cmd	**cmds)
{
	t_cmd	*temp;

	while (*cmds)
	{
		temp = (*cmds)->next;
		free_2d_char((*cmds)->tokens);
		free_2d_char((*cmds)->args);
		free_2d_char((*cmds)->redirs);
		free_2d_char((*cmds)->limiter_arr);
		if ((*cmds)->path)
			free((*cmds)->path);
		free(*cmds);
		*cmds = temp;
	}
}

int	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
{
	int	k;

	k = 0;
	cmd->tokens = ft_calloc(*n - *i + 2, sizeof(char *));
	while (shell->tokens && shell->tokens[*i] && *i < *n)
	{
		cmd->tokens[k] = ft_strdup(shell->tokens[*i]);
		k++;
		(*i)++;
	}
	cmd->has_hd = 0;
	cmd->built_in = 0;
	make_arg_array(cmd, shell);
	make_redir_array(cmd, shell);
	make_limiter_arr(cmd);
	return (0);
}

int	edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	if (!cmds)
	{
		return (0);
	}
	while (shell->tokens && shell->tokens[n]
		&& !is_pipe(shell->tokens[n]))
		n++;
	if(init_cmd(shell, cmds, &i, &n))
		return (1);
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
	return (0);
}
