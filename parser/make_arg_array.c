/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/24 17:18:37 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

void	make_arg_array(t_cmd *cmd, t_shelldata *shell)
{
	int i;
	int n;
	int is_echo;

	i = 0;
	n = 0;
	is_echo = (cmd->tokens[0] && ft_strcmp(cmd->tokens[0], "echo") == 0);
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
			if (is_echo)
				cmd->args[n] = expand(cmd->tokens[i], shell);
			else
				cmd->args[n] = remove_quotes(expand(cmd->tokens[i], shell));
			n++;
		}
		i++;
	}
}
