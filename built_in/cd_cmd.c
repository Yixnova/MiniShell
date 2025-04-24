/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:39 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/22 09:09:38 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

void	pwd(void)
{
	char	cwd[BUFFER_SIZE];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", cwd);
}

void	cd_command(char *path, t_shelldata *shell)
{
	int		ret;
	char	*home;

	ret = 0;
	home = NULL;
	if (!path)
	{
		home = getenv("HOME");
		path = home;
	}
	ret = chdir(path);
	if (ret != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 1;
	}
	else
		shell->exit_status = 0;
}
