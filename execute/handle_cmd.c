/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: busseven <busseven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:24:57 by yigsahin          #+#    #+#             */
/*   Updated: 2025/05/26 13:33:27 by busseven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"

char	*ft_myjoin(const char *s1, const char *s2, const char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	free(temp);
	return (result);
}

int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	execute_builtin(t_shelldata *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		echo_command(args);
	else if (!ft_strcmp(args[0], "cd"))
	{
		shell->exit_status = cd_command(args[1]);
		exit(shell->exit_status);
	}
	else if (!ft_strcmp(args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(args[0], "export"))
		export_command(&shell->env, args, shell);
	else if (!ft_strcmp(args[0], "unset"))
		unset_command(&shell->env, args);
	else if (!ft_strcmp(args[0], "env"))
		env_command(shell, args);
	else if (!ft_strcmp(args[0], "exit"))
		exit_command(args, shell);
	else
		return (0);
	return (1);
}

int	handle_builtin_command(t_shelldata *shell, char **args)
{
	if (!args || !args[0] || !is_builtin_command(args[0]))
		return (0);
	return (execute_builtin(shell, args));
}

void	check_files_and_path(t_cmd *cmd, t_shelldata *shell, int pid)
{
	if (pid == 0 && open_files(cmd, shell))
		exit(1);
	if (cmd->args && cmd->args[0] && !is_file_dir_name(cmd->args[0]))
		check_builtin_and_path(cmd, shell);
	if (cmd->args && cmd->args[0] && is_file_dir_name(cmd->args[0]))
		cmd->path = ft_strdup(cmd->args[0]);
	if (cmd->args && cmd->args[0] && cmd->args[0][0] == '.'
		&& ft_strlen(cmd->args[0]) == 1)
	{
		if(pid == 0)
			single_dot_error();
		cmd->err_type = 1;	
	}
	else if (cmd->args && cmd->args[0] && cmd->args[0][0] == '\0')
	{
		cmd->invalid = 1;
		command_not_found(cmd, cmd->args[0]);
	}
	else if (cmd->args && cmd->args[0] && cmd->invalid
		&& !is_file_dir_name(cmd->args[0]))
		command_not_found(cmd, cmd->args[0]);
	else if (cmd->args && cmd->args[0] && is_all_dots(cmd->args[0]))
		command_not_found(cmd, cmd->args[0]);
}
