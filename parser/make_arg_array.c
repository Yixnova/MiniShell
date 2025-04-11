/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_arg_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 13:28:56 by busseven          #+#    #+#             */
/*   Updated: 2025/04/11 17:44:53 by busseven         ###   ########.fr       */
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

void	copy_arg(t_cmd	*cmd)
{
}

void	make_arg_array(t_cmd *cmd)
{
}
