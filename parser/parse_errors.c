/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 13:19:20 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int	is_valid_redir(char	*str)
{
	if(!strncmp(str, ">", sizeof(str)))
		return (1);
	if(!strncmp(str, ">>", sizeof(str)))
		return (1);
	if(!strncmp(str, "<<", sizeof(str)))
		return (1);
	if(!strncmp(str, "<", sizeof(str)))
		return (1);
	return (0);
}
int	check_parse_errors(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*redir;

	i = 0;
	if(cmd->arg_count < 1)
	{
		printf("parse error near token '|'\n");
		return (1);
	}
	while(cmd->redirs[i])
	{
		n = 0;
		while(cmd->redirs[i][n] != ' ')
			n++;
		redir = ft_substr(cmd->redirs[i], 0, n);
		if(!is_valid_redir(redir))
		{
			printf("parse error near redir\n");
			free(redir);
			return (1);
		}
		free(redir);
		i++;
	}
	return (0);
}
