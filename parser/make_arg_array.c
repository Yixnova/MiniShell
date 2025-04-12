/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 09:51:52 by busseven         ###   ########.fr       */
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
	if(!str)
		return (0);
	if(str[0] && (str[0] == '<' || str[0] == '>'))
		return (1);
	return (0);
}

void	make_arg_array(t_cmd *cmd, t_shelldata *shell)
{
	int	i;
	int	n;
	int	count;

	i = 0;
	n = 0;
	count = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
			i++;
		else
			count++;
		i++;
	}
	i = 0;
	cmd->args = ft_calloc(count + 1, sizeof(char *));
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
			i++;
		else
		{
			cmd->args[n] = remove_quotes(expand_string(cmd->tokens[i], shell));
			n++;
		}
		i++;
	}
}
