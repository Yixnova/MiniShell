/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 16:39:19 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

void	make_arg_array(t_cmd *cmd, t_shelldata *shell)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
			i++;
		else
			cmd->arg_count++;
		i++;
	}
	i = 0;
	cmd->args = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	while (cmd->tokens[i])
	{
		if (is_redir(cmd->tokens[i]))
			i++;
		else
		{
			cmd->args[n] = remove_quotes(expand(cmd->tokens[i], shell));
			n++;
		}
		i++;
	}
}
