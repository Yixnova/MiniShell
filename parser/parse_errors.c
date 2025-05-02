/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/05/02 15:33:31 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

int	syntax_error(char *token)
{
	write(2, "minishell: ", 12);
	write(2, "syntax_error in token: ", 24);
	write(2, token, ft_strlen(token));
	write(2, "\n", 1);
	return (1);
}
int	check_syntax_errors(t_cmd *cmd)
{
	int	i;
	int	redir;
	int	n;

	i = 0;
	n = 0;
	while(cmd->redirs[i])
	{
		n = 0;
		while(cmd->redirs[i][n] && cmd->redirs[i][n] != ' ')
			n++;
		if(n > 2)
			syntax_error(cmd->redirs[i]);
		redir = cmd->redirs[i][0];
		n = 1;
		while(cmd->redirs[i][n] && cmd->redirs[i][n] != ' ')
		{
			if(cmd->redirs[i][n] != redir)
				return(syntax_error(cmd->redirs[i]));
			n++;	
		}
	}
	return (0);
}
