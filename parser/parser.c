/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 14:10:05 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	make_limiter_array(cmd, shell);
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
		//free cmd list, return 1.
	}
	edit_cmds_arr(shell, cmds->next, i + 1, n + 1);
	return (0);
}