/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/04/25 09:43:52 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int	check_parse_errors(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*redir;

	i = 0;

	while (cmd->redirs[i])
	{
		n = 0;
		while (cmd->redirs[i][n] && cmd->redirs[i][n] != ' ')
			n++;
		redir = ft_substr(cmd->redirs[i], 0, n);
		if (!redir_num(redir) || !cmd->redirs[i][n + 1])
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
