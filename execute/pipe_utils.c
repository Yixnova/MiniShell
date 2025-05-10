/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 12:01:01 by busseven          #+#    #+#             */
/*   Updated: 2025/05/10 12:01:17 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	close_all_pipes(t_shelldata *shell)
{
	int i;

	i = 0;
	while(i < shell->cmd_count - 1)
	{
		free(shell->pipes[i]);
		i++;
	}
}
void	close_pipes(t_shelldata *shell, int i)
{
	if(i != 0)
	{
		close(shell->pipes[i - 1][0]);
		close(shell->pipes[i - 1][1]);	
	}
}