/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 11:56:32 by busseven          #+#    #+#             */
/*   Updated: 2025/06/05 19:10:55 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_directory(const char *path)
{
	struct stat	file;

	if (!is_file_dir_name(path))
		return (0);
	if (lstat(path, &file) == 0 && S_ISDIR(file.st_mode))
		return (1);
	return (0);
}

int	is_simple_cd_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
}

int	is_simple_export_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "export") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
}

int	is_simple_unset_command(t_cmd *cmd, t_shelldata *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (shell->cmd_count != 1)
		return (0);
	if (ft_strcmp(cmd->args[0], "unset") != 0)
		return (0);
	if (cmd->redir_count != 0 || cmd->output_type != 0 || cmd->input_type != 0)
		return (0);
	return (1);
}

int	is_file_dir_name(const char *file)
{
	int	i;

	i = 0;
	while (file[i] == '.')
		i++;
	if (file[i] == '/')
		return (1);
	return (0);
}
