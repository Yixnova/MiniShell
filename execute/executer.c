/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/12 16:50:51 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_processes(t_shelldata *shell, t_cmd **cmds)
{
	int		pid;
	int		status;
	t_cmd	*temp;
	
	temp = *cmds;
	while(*cmds)
	{
		pid = fork();
		if(pid == 0)
		{
			//dosyaları açan fonksiyon yazılacak
			//hangi dosyaya yönlendirme yapılacağını belirleyen fonk.
			//yigitin yazdığın executer buraya gelecek
		}
		*cmds = (*cmds)->next;
	}
	waitpid(pid, &status, 0);
	if(WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
		printf("%d\n", WEXITSTATUS(status));
	}
	*cmds = temp;
}
