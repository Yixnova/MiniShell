/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/09 15:08:13 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"minishell.h"

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
void	make_arg_array(t_cmd *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(cmd->tokens[i])
	{
		if(is_redir(cmd->tokens[i]))
			i++;
		else
			count++;
		i++;
	}
	cmd_args = ft_calloc(count + 1, sizeof(char *));
}
