/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:39 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/19 14:10:24 by yigsahin         ###   ########.fr       */
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

void	cd_command(char *path)
{
	const char	*dir;

	if (path == NULL)
	{
		dir = getenv("HOME");
		if (!dir)
		{
			write(2, "cd: HOME not set\n", 18);
			return ;
		}
	}
	else
		dir = path;
	if (chdir(dir) != 0)
	{
		perror("cd");
	}
}
