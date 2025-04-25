/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 13:34:29 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int		is_empty_str(char *str)
{
	if(str && str[0] == '\0')
		return (1);
	return (0);
}
void	make_arg_array(t_cmd *cmd, t_shelldata *shell)
{
	int		i;
	int		n;
	char	*expanded;

	i = 0;
	n = 0;
	while (cmd->tokens[i])
	{
		expanded = expand(cmd->tokens[i], shell);
		if(is_redir(cmd->tokens[i]))
			i++;
		else if(!is_empty_str(expanded))
			cmd->arg_count++;
		free(expanded);
		i++;
	}
	i = 0;
	cmd->args = ft_calloc(cmd->arg_count + 1, sizeof(char *));
	while (cmd->tokens[i])
	{
		expanded = expand(cmd->tokens[i], shell);
		if (is_redir(cmd->tokens[i]))
			i++;
		else if(!is_empty_str(expanded))
		{
			cmd->args[n] = remove_quotes(expand(cmd->tokens[i], shell));
			n++;
		}
		free(expanded);
		i++;
	}
}
