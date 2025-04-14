/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 09:41:18 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_cmd(t_shelldata *shell, t_cmd *cmd, int *i, int *n)
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
	int z = 0;
	printf("tokens:\n");
	while(cmd->tokens[z])
	{
		printf("%s\n", cmd->tokens[z]);
		z++;
	}
	make_arg_array(cmd, shell);
	printf("args:\n");
	z = 0;
	while(cmd->args[z])
	{
		printf("%s\n", cmd->args[z]);
		z++;
	}
	make_redir_array(cmd, shell);
	printf("redirs:\n");
	z = 0;
	while(cmd->redirs[z])
	{
		printf("%s\n", cmd->redirs[z]);
		z++;
	}
	pipe(cmd->pipe);
	printf("next cmd:\n");
}

void	edit_cmds_arr(t_shelldata *shell, t_cmd *cmds, int i, int n)
{
	if (!cmds)
	{
		printf("no cmd\n");
		return ;
	}
	while (shell->tokens && shell->tokens[n] && !is_pipe(shell->tokens[n]))
		n++;
	init_cmd(shell, cmds, &i, &n);
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
}
