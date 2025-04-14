/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:43:40 by busseven          #+#    #+#             */
/*   Updated: 2025/04/14 18:49:41 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	if(!cmd->prev)
//		cmd->input = 0;
//	else
//		cmd->input = cmd->prev->pipe[0];
//	if(cmd->next)
//		cmd->output = cmd->prev->pipe[1];
//	else
//		cmd->output = 1;

void	open_files(t_cmd *cmd)
{
	int		i;
	int		n;
	char	*file_name;

	i = 0;
	n = 0;
	cmd->fd_count = cmd->redir_count - cmd->hd_count
	cmd->file_descs = ft_calloc(cmd->fd_count, sizeof(int));
	while(cmd->redirs[i])
	{
		file_name = cmd->redirs[i] + is_in_str(cmd->redirs[i], ' ');
		if(has_valid_redir(cmd->redirs[i]))
		{
			if(has_valid_redir(cmd->redirs[i]) == 1)
				cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 777);
			else if(has_valid_redir(cmd->redirs[i]) == 2)
				cmd->file_descs[n] = open(file_name, O_RDWR | O_CREAT | O_APPEND, 777);
			else if(has_valid_redir(cmd->redirs[i]) == 4)
				cmd->file_descs[n] = open(file_name, O_RDONLY);
			if(cmd->file_descs[n] < 0)
				//error:no such file
			n++;
		}
		i++;
	}
}

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
			open_files(t_cmd *cmds);
			//hangi dosyaya yönlendirme yapılacağını belirleyen fonk.
			//yigitin yazdığın executer buraya gelecek
			exit(1);
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
