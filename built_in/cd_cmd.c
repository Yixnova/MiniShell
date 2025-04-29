/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yigsahin <yigsahin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:53:39 by yigsahin          #+#    #+#             */
/*   Updated: 2025/04/29 17:48:08 by yigsahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/built_in.h"

void	pwd(void)
{
	char	cwd[BUFFER_SIZE];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("pwd");
		exit(1);
	}
	printf("%s\n", cwd);
	exit(0);
}

int	cd_command(char *path)
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
		return (1);
	}
	return (0);
}

static void update_oldpwd_env(t_env **env, t_env *pwd)
{
	char *old;
	t_env *oldpwd;

	oldpwd = find_env(*env, "OLDPWD");
	if (pwd && pwd->value)
		old = ft_strdup(pwd->value);
	else
		old = ft_strdup("");
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = old;
	}
	else
		set_env(env, "OLDPWD", old);
}

void update_pwd_env(t_env **env)
{
	char cwd[BUFFER_SIZE];
	t_env *pwd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return;
	pwd = find_env(*env, "PWD");
	update_oldpwd_env(env, pwd);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = ft_strdup(cwd);
	}
	else
		set_env(env, "PWD", cwd);
}
