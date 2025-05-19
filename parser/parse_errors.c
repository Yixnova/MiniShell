/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/05/19 19:32:18 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../inc/minishell.h"

void	heredoc_eof(t_cmd *cmd, int line_num, int h, char *line)
{
	close(cmd->hd_arr[h][1]);
	printf("warning: ");
	printf("here-document at line %d ", line_num);
	printf("delimited by end-of-file (wanted `%s')\n", cmd->limiter_arr[h]);
	free(line);
	exit(0);
}
