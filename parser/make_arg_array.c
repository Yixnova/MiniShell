/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/10 15:23:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int		is_pipe(char *str)
{
	if(!ft_strncmp(str, "|", ft_strlen(str)))
		return (1);
	return (0);
}

int		is_redir(char	*str)
{
	if(!ft_strncmp(str, ">", ft_strlen(str)))
		return (1);
	else if(!ft_strncmp(str, "<", ft_strlen(str)))
		return (1);
	else if(!ft_strncmp(str, ">>", ft_strlen(str)))
		return (1);
	else if(!ft_strncmp(str, "<<", ft_strlen(str)))
		return (1);
	return (0);
}

void	copy_arg(t_cmd	*cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while(cmd->tokens[i])
	{
		while(is_redir(cmd->tokens[i]))
			i++;
		if(i > 0 && is_redir(cmd->tokens[i - 1]))
			i++;
		else
			cmd->args[n++] = remove_quotes(cmd->tokens[i++]);
	}
}

void	make_arg_array(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
		{
			while(is_redir(cmd->tokens[i]))
				i++;
		}
		else
			count++;
		i++;
	}
	cmd->args = ft_calloc(count + 1, sizeof(char *));
	copy_arg(cmd);
}
