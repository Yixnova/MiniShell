/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:24:57 by busseven          #+#    #+#             */
/*   Updated: 2025/04/09 12:28:36 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		*ft_intjoin(int	*arr, int n)
{
	int	i;
	int	*new;

	i = 0;
	if(!arr)
		arr = ft_calloc(1, sizeof(int));
	while(arr[i])
		i++;
	new = ft_calloc(i + 1, sizeof(int));
	i = 0;
	while(arr[i])
	{
		new[i] = arr[i];
		i++;
	}
	new[i] = n;
	free(arr);
	return(new);
}

void	find_pipe(char **arr, int *n)
{
	while(arr[n] && !is_pipe(arr[n]))
		(*n)++;
}
void	init_parsedata(t_shelldata *shell)
{
	shell->cmds = ft_calloc(1, sizeof(t_cmd));
	shell->cmds
}

void	parser(t_shelldata *shell, t_cmd *cmd, int i, int n)
{
	int	pid;
	int	status;

	pid = fork();
	find_pipe(shell->token_arr, *n);
	if(pid == 0)
	{
		init_parsedata(shell);
	}
	else
	{
		parser(shell, cmd->next, n + 1, n + 1);
	}
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
	{
		//child'ın exit statusunu çeker
		shell->exit = WEXITSTATUS(status);
	}
}
