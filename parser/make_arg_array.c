/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/05/30 14:00:24 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_empty_str(char *str)
{
	if (str && str[0] == '\0')
		return (1);
	return (0);
}

void	add_args(t_shelldata *shell, t_cmd *cmd)
{
	int		i;
	int		n;
	char	*expanded;

	i = 0;
	n = 0;
	while (cmd->tokens[i])
	{
		expanded = expand(cmd->tokens[i], shell, 0);
		if (is_redir(cmd->tokens[i]))
			i++;
		else if (!is_empty_str(expanded))
		{
			cmd->args[n] = rm_quotes(expand(cmd->tokens[i], shell, 0), 1);
			n++;
		}
		free(expanded);
		i++;
	}
}

void	make_arg_array(t_cmd *cmd, t_shelldata *shell)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->tokens[i])
	{
		expanded = expand(cmd->tokens[i], shell, 0);
		if (is_redir(cmd->tokens[i]))
			i++;
		else if (!is_empty_str(expanded))
			cmd->arg_count++;
		free(expanded);
		i++;
	}
	cmd->args = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	add_args(shell, cmd);
}
