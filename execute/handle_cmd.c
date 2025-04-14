/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 09:24:57 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/14 09:24:59 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_arrfree(char **arr)
{
	int i;

	if (!arr)
		return;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

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

static int	is_builtin_command(const char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
			!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
			!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
			!ft_strcmp(cmd, "exit"));
}

static int	execute_builtin(t_shelldata *shell, char **args)
{
	if (!ft_strcmp(args[0], "echo"))
		echo_command(args);
	else if (!ft_strcmp(args[0], "cd"))
		cd_command(args[1]);
	else if (!ft_strcmp(args[0], "pwd"))
		pwd();
	else if (!ft_strcmp(args[0], "export"))
		export_command(&shell->env, args);
	else if (!ft_strcmp(args[0], "unset"))
		unset_command(&shell->env, args);
	else if (!ft_strcmp(args[0], "env"))
		env_command(shell->env, args);
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
