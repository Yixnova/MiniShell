/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:53:00 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:13:02 by yigsahin         ###   ########.fr       */
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
